cmake_minimum_required(VERSION 3.5)
project(solitare)

# Enable all warnings.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Optimize for current platform.
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")

# Use C++14.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(solitare src/board.cpp src/main.cpp src/progress.cpp)
