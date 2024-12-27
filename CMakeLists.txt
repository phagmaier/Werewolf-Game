cmake_minimum_required(VERSION 3.22)
project(Project)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Always use -O3 optimization
set(CMAKE_CXX_FLAGS "-O3")

# Find the raylib package
find_package(raylib REQUIRED)

# List the source files
set(SOURCES
    src/main.cpp
    src/Player.cpp
    src/Selector.cpp
    src/Timer.cpp
)

# Define the executable
add_executable(runme ${SOURCES})

# Link the raylib library
target_link_libraries(runme raylib)

