cmake_minimum_required(VERSION 3.10)

# set the project name
project(Fuoco VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(libs/shader)
include_directories(libs/stb_image)
include_directories(libs/glm-0.9.9.8)

# GLFW
add_subdirectory(libs/glfw-3.3.4)
include_directories(libs/glfw-3.3.4/include)
list(APPEND EXTRA_LIBS glfw)
list(APPEND EXTRA_LIBS ${glfw_LIBRARIES})
# list(APPEND EXTRA_LIBS ${OPENGL_LIBRARY}) 

# GLAD
include_directories(libs/glad/include)

configure_file(src/FuocoConfig.h.in ${PROJECT_SOURCE_DIR}/src/FuocoConfig.h)

# add the executable
add_executable(Fuoco src/main.cpp libs/glad/src/glad.c)

target_link_libraries(Fuoco PUBLIC ${EXTRA_LIBS})

target_include_directories(Fuoco PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

file(COPY src/shaders/ DESTINATION shaders)
file(COPY src/assets/ DESTINATION assets)

install(TARGETS Fuoco DESTINATION bin)                      
install(FILES "${PROJECT_BINARY_DIR}/src/FuocoConfig.h" DESTINATION include)