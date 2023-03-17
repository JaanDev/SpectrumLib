cmake_minimum_required(VERSION 3.1)
project(Spectrum VERSION 1.0.0 DESCRIPTION "A simple library for graphics developing")

set(CMAKE_POSITION_INDEPENDENT_CODE True)

macro(setoption option value)
    set(${option} ${value} CACHE INTERNAL "" FORCE)
endmacro()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
# set(CMAKE_CXX20_STANDARD_COMPILE_OPTION "-std:c++latest")
# set(CMAKE_CXX20_EXTENSION_COMPILE_OPTION "-std:c++latest")
# set(CMAKE_CXX20_STANDARD_COMPILE_OPTION "-std=c++latest")
# set(CMAKE_CXX20_EXTENSION_COMPILE_OPTION "-std=c++latest")

file(GLOB SOURCES
    src/*.cpp
)

file(GLOB GLEW_SOURCES
    external/glew/src/*.c
)

setoption(GLFW_BUILD_EXAMPLES OFF)
setoption(GLFW_BUILD_TESTS OFF)
setoption(GLFW_BUILD_DOCS OFF)
setoption(GLFW_INSTALL OFF)
add_subdirectory(external/glfw)

add_subdirectory(external/glew/build/cmake)

add_subdirectory(external/fmt)

if (UNIX)
    find_package(OpenGL REQUIRED)
    set(SPECTRUM_GL_INCLUDES ${OPENGL_INCLUDE_DIRS})
    set(SPECTRUM_GL_LIBS ${OPENGL_LIBRARIES})

else()
    set(SPECTRUM_GL_INCLUDES "")
    set(SPECTRUM_GL_LIBS opengl32)
endif()

add_library(Spectrum STATIC ${SOURCES})
target_include_directories(Spectrum PUBLIC external/glew/include include ${SPECTRUM_GL_INCLUDES})
target_link_libraries(Spectrum PUBLIC glfw ${SPECTRUM_GL_LIBS} glew fmt::fmt)

# add_library(Spectrum_shared SHARED ${SOURCES})
# target_include_directories(Spectrum_shared PUBLIC include)
# set_target_properties(Spectrum_shared PROPERTIES OUTPUT_NAME Spectrum)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    add_subdirectory(tests)
endif()