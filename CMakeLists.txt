cmake_minimum_required(VERSION 3.5.0)
project(SpectrumLib VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

function(setOption name value type)
    set(${name} ${value} CACHE ${type} "" FORCE)
endfunction()

option(SPECTRUM_SHARED_LIBRARY "Build a shared library for SpectrumLib" OFF)
option(SPECTRUM_BUILD_EXAMPLES "Build examples for SpectrumLib" OFF)

setOption(RAPIDJSON_BUILD_DOC OFF BOOL)
setOption(RAPIDJSON_BUILD_EXAMPLES OFF BOOL)
setOption(RAPIDJSON_BUILD_TESTS OFF BOOL)

add_subdirectory(external/glfw)
add_subdirectory(external/fmt)
add_subdirectory(external/glm)
add_subdirectory(external/rapidjson)
add_subdirectory(external/utfcpp)

file(GLOB SOURCES
    src/*.cpp
    external/glad/src/gl.c
    external/stb/*.c
)

set(SPECTRUM_LIB_TYPE STATIC)
if (${SPECTRUM_SHARED_LIBRARY})
    set(SPECTRUM_LIB_TYPE SHARED)
endif()

message(STATUS "SPL: Building ${SPECTRUM_LIB_TYPE} library")
add_library(${PROJECT_NAME} ${SPECTRUM_LIB_TYPE} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glm RapidJSON utf8cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt)
target_include_directories(${PROJECT_NAME} PUBLIC
    src
    external/glad/include
    external/rapidjson/include
)
target_include_directories(${PROJECT_NAME} PRIVATE
    external/stb
)
if (${SPECTRUM_LIB_TYPE} MATCHES SHARED)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SPECTRUM_SHARED)
endif()

if (${SPECTRUM_BUILD_EXAMPLES} OR ${CMAKE_CURRENT_SOURCE_DIR} MATCHES ${CMAKE_SOURCE_DIR})
    message(STATUS "SPL: Building examples")
    add_subdirectory(examples)
else()
    message(STATUS "SPL: Not building examples")
endif()