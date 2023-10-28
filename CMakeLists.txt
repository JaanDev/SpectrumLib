cmake_minimum_required(VERSION 3.5.0)
project(SpectrumLib VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/glfw)
add_subdirectory(external/fmt)

file(GLOB SOURCES
    src/*.cpp
    external/glad/src/gl.c
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw fmt)
target_include_directories(${PROJECT_NAME} PUBLIC
    src
    external/glad/include
)

add_subdirectory(examples/window)