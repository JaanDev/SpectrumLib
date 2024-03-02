cmake_minimum_required(VERSION 3.5.0)
project(SpectrumLib VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

function(setOption name value type)
    set(${name} ${value} CACHE ${type} "" FORCE)
endfunction()

option(SPECTRUM_SHARED_LIBRARY "Build a shared library for SpectrumLib" OFF)
option(SPECTRUM_BUILD_EXAMPLES "Build examples for SpectrumLib" OFF)

setOption(CPM_USE_LOCAL_PACKAGES ON BOOL)
include(cmake/CPM.cmake)

CPMAddPackage(
    NAME glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
CPMAddPackage("gh:nemtrif/utfcpp#v4.0.5")
CPMAddPackage(
    NAME glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
CPMAddPackage(
    NAME rapidjson
    GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
    GIT_TAG 3f73edae00aba5b0112a80b4d41e6f1ff7d92a3d
    DOWNLOAD_ONLY YES
)
CPMAddPackage(
    NAME stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG ae721c50eaf761660b4f90cc590453cdb0c2acd0
    DOWNLOAD_ONLY YES
)
CPMAddPackage(
    NAME miniaudio
    GIT_REPOSITORY https://github.com/mackron/miniaudio.git
    GIT_TAG 0.11.21
    DOWNLOAD_ONLY YES
)

file(GLOB SOURCES
    src/*.cpp
    external/glad/src/gl.c
    ${stb_SOURCE_DIR}/*.c
)

set(SPECTRUM_LIB_TYPE STATIC)
if (${SPECTRUM_SHARED_LIBRARY})
    set(SPECTRUM_LIB_TYPE SHARED)
endif()

message(STATUS "SPL: Building ${SPECTRUM_LIB_TYPE} library")
add_library(${PROJECT_NAME} ${SPECTRUM_LIB_TYPE} ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PUBLIC GLM_ENABLE_EXPERIMENTAL _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glm utf8cpp)
target_include_directories(${PROJECT_NAME} PUBLIC
    src
    external/glad/include
    ${rapidjson_SOURCE_DIR}/include
    ${stb_SOURCE_DIR}
    ${miniaudio_SOURCE_DIR}
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