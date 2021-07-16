cmake_minimum_required(VERSION 3.10)

# set the project name
project(Fuoco VERSION 1.0)

configure_file(./src/FuocoConfig.h.in ./src/FuocoConfig.h)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(Fuoco src/main.cpp)

target_include_directories(Fuoco PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )