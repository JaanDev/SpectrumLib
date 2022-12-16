cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 17)
project(Spectrum VERSION 1.0)

file(GLOB SOURCES
	"tests/*.cpp"
	"libs/SpectrumLib/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
add_subdirectory(libs/raylib)
target_link_libraries(${PROJECT_NAME} raylib)
target_include_directories(${PROJECT_NAME} PRIVATE
	"include"
	"libs/SpectrumLib"
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
