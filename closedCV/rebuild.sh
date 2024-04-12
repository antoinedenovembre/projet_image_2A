#!/bin/zsh

# GLOBAL VARIABLES
SOURCE_DIR=$(pwd)
BUILD_DIR="build"
APP_NAME="app"

# OPTIONS
IS_FORCE_REBUILD=false
IS_FORMAT_ENABLED=false
IS_RUN_ENABLED=false

# Color variables for styling output
RED='\033[0;31m'
GREEN='\033[0;32m'
BOLD='\033[1m'
ITALIC='\033[3m'
UNDERLINE='\033[4m'
NC='\033[0m'

# Function to print an error message
print_error() {
	echo -e "${RED}${BOLD}Error: ${NC}${1}"
}

# Function to print a success message
print_success() {
	echo -e "${GREEN}${BOLD}Success: ${NC}${1}"
}

# Function to print informational message
print_info() {
	echo -e "${ITALIC}${1}${NC}"
}

# Function to print a title
print_title() {
	echo -e "${BOLD}${UNDERLINE}${1}${NC}"
}

newline() {
	echo ""
}

# Trap Ctrl+C and exit
ctrl_c() {
	print_error "Build process interrupted"
	exit 1
}

cleanup() {
  tput cnorm  # Show cursor
}

trap ctrl_c INT
trap cleanup EXIT

# Function to parse command line arguments
parse_args() {
	while getopts "hfre" opt; do
		case $opt in
			h)
				echo "Usage: ./rebuild.sh [-e] [-f] [-r] [-h]"
				echo "Options:"
				echo "  -e  Execute the program after building"
				echo "  -f  Force rebuild (removes and recreates build directory)"
				echo "  -r  Format code using clang-format"
				echo "  -h  Display this help message"
				exit 0
				;;
			f)
				IS_FORCE_REBUILD=true
				;;
			r)
				IS_FORMAT_ENABLED=true
				;;
			e)
				IS_RUN_ENABLED=true
				;;
			\?)
				print_error "Invalid option: -$OPTARG"
				exit 1
				;;
		esac
	done
}

# Function to manage the build directory
manage_build_dir() {
	if [ "$IS_FORCE_REBUILD" = true ]; then
		print_info "Deleting build directory..."
		rm -rf $BUILD_DIR
	fi
	if [ ! -d "$BUILD_DIR" ]; then
		print_info "Creating build directory..."
		mkdir $BUILD_DIR
	fi

	print_success "Build directory is ready"
}

# Function to format code using clang-format
format_code() {
	if [ "$IS_FORMAT_ENABLED" = true ]; then
		print_info "Formatting code..."
		find . -iname '*.h' -o -iname '*.cpp' -o -iname '*.hpp' | while read -r file; do
			clang-format -i "$file" -style=file
		done
		print_success "Code formatted successfully"
	fi
}

# Function to build the project with a simple progress bar simulation
build_project() {
	cd "$SOURCE_DIR" || { print_error "Source directory not found"; exit 1; }

	print_info "Emptying res directory..."
	
	rm -rf res
	mkdir res

    cd "$SOURCE_DIR/$BUILD_DIR" || { print_error "Build directory not found."; exit 1; }

    print_info "Configuring project with CMake..."
    if ! cmake .. > /dev/null 2>&1; then
        print_error "CMake configuration failed"
        exit 1
    fi

    print_info "Compiling project..."
    
    # Start spinner in the background
    spinner $! & 
    spinner_pid=$!

    # Run make command and redirect output to a log file
    make -j$(sysctl -n hw.ncpu) > build.log 2>&1
    local make_status=$?
    
    # Kill spinner
	if [ -n "$spinner_pid" ] && ps -p $spinner_pid > /dev/null; then
		kill $spinner_pid
		wait $spinner_pid 2>/dev/null
	fi
    
    echo # Ensure newline

    if [ $make_status -ne 0 ]; then
        print_error "Build failed. Check build.log for details"
        exit $make_status
    else
        print_success "Project built successfully"
    fi
}

spinner() {
    local pid=$!
    local delay=0.25
    local spinstr='|/-\'
	tput civis
    while [ "$(ps a | awk '{print $1}' | grep $pid)" ]; do
        local temp=${spinstr#?}
        printf " [%c]  " "$spinstr"
        local spinstr=$temp${spinstr%"$temp"}
        sleep $delay
        printf "\b\b\b\b\b\b"
    done
    printf "    \b\b\b\b"
	tput cnorm
}

run_project() {
	cd $SOURCE_DIR || { print_error "Source directory not found"; exit 1; }
	./$BUILD_DIR/$APP_NAME
}

main() {
	parse_args "$@"

	print_title "Build directory setup"
	manage_build_dir
	newline
	if [ "$IS_FORMAT_ENABLED" = true ]; then
		print_title "Code formatting"
		format_code
		newline
	fi
	print_title "Building project"
	build_project
	if [ "$IS_RUN_ENABLED" = true ]; then
		clear
		print_title "Running project"
		run_project
	fi
}

main "$@"
