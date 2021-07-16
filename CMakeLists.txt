cmake_minimum_required(VERSION 3.10)

# set the project name
project(Fuoco VERSION 1.0)

option(USE_MYMATH "Use tutorial provided math implementation" ON)

if(USE_MYMATH)
  add_subdirectory(libs/math)
  list(APPEND EXTRA_LIBS Math)
  list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/Math")
endif()

configure_file(./src/FuocoConfig.h.in ./src/FuocoConfig.h)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(Fuoco src/main.cpp)

target_link_libraries(Fuoco PUBLIC ${EXTRA_LIBS})

target_include_directories(Fuoco PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${EXTRA_INCLUDES}"
                           )