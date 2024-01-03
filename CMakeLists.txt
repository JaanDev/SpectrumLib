cmake_minimum_required(VERSION 3.5.0)
project(SpectrumLib VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

function(setOption name value type)
    set(${name} ${value} CACHE ${type} "" FORCE)
endfunction()

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

add_library(${PROJECT_NAME} STATIC ${SOURCES})
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

message(STATUS "SPL: Building examples")
add_subdirectory(examples)