BLACK     =    \033[0;30m
RED       =    \033[0;31m
GREEN     =    \033[0;32m
ORANGE    =    \033[0;33m
BLUE      =    \033[0;34m
PURPLE    =    \033[0;35m
CYAN      =    \033[0;36m
LIGHT_GRAY =  \033[0;37m
DARK_GRAY  =  \033[1;30m
LIGHT_RED  =  \033[1;31m
LIGHT_GREEN = \033[1;32m
YELLOW     =  \033[1;33m
LIGHT_BLUE =  \033[1;34m
LIGHT_PURPLE = \033[1;35m
LIGHT_CYAN =  \033[1;36m
WHITE      =  \033[1;37m
NO_COLOR   =  \033[0m

NAME = app.a

SRCS = main.cpp
INCLUDES = -I ./include
OBJS = $(SRCS:.cpp=.o)

# Library related variables
LIB_NAME = closedCV
LIB_SRCS = ./source/ImageCouleur.cpp \
           ./source/ImageNdg.cpp \
		   ./source/ImageDouble.cpp \
		   ./source/ImageClasse.cpp
LIB_OBJS = $(LIB_SRCS:.cpp=.o)

CC = g++
FLAGS = -Wall -Wextra -Werror -Wno-unused-variable -std=c++11

RM = rm -f


all: $(LIB_NAME) $(NAME) clean

# Makes and runs the program
run: all
	clear
	@echo "Running $(NAME)..."
	@./$(NAME)

# Pre-compilation
.cpp.o:
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $(<:.cpp=.o)
	@printf "\033[2K\r$(BLUE)$(NAME): $(PURPLE)$<$(NO_COLOR)"

# Rule to make the library
$(LIB_NAME): $(LIB_OBJS)
	@ar rc lib$(LIB_NAME).a $(LIB_OBJS)
	@ranlib lib$(LIB_NAME).a
	@printf "\033[2K\r$(BLUE)$(LIB_NAME): $(GREEN)Compiled [√]$(NO_COLOR)\n"

# Rule to make the executable
$(NAME): $(OBJS)
	@rm -rf res/
	@mkdir res/
	@$(CC) $(FLAGS) $(INCLUDES) -L. -l$(LIB_NAME) $(OBJS) -o $(NAME)
	@printf "\033[2K\r$(BLUE)$(NAME): $(GREEN)Compiled [√]$(NO_COLOR)\n"

# Deletes .o files
clean:
	@$(RM) $(OBJS) $(LIB_OBJS)

# Deletes .o files and library
fclean: clean
	$(RM) $(NAME) $(LIB_NAME)

# Deletes .o files and library and recompiles
re: fclean all

# Specifies that the following rules are not associated with files
.PHONY: all clean fclean re run .cpp.o
