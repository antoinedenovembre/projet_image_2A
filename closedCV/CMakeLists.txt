cmake_minimum_required(VERSION 3.10)
project(ClosedCV)

set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(include)

# Add library
add_library(closedCV STATIC
  source/ImageCouleur.cpp
  source/ImageNdg.cpp
  source/ImageDouble.cpp
  source/ImageClasse.cpp
)

# Add executable
add_executable(app main.cpp)

# Link the executable to the library
target_link_libraries(app closedCV)