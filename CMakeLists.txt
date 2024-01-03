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
CPMAddPackage("gh:glfw/glfw#3.3.9")
CPMAddPackage("gh:fmtlib/fmt#10.2.0")
CPMAddPackage("gh:nemtrif/utfcpp#v4.0.5")
CPMAddPackage(
    NAME glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG b06b775c1c80af51a1183c0e167f9de3b2351a79
)
CPMAddPackage(
    NAME rapidjson
    GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
    GIT_TAG 6089180ecb704cb2b136777798fa1be303618975
    DOWNLOAD_ONLY YES
)
CPMAddPackage(
    NAME stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG f4a71b13373436a2866c5d68f8f80ac6f0bc1ffe
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
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glm utf8cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt)
target_include_directories(${PROJECT_NAME} PUBLIC
    src
    external/glad/include
    ${rapidjson_SOURCE_DIR}/include
    ${stb_SOURCE_DIR}
    external/miniaud
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