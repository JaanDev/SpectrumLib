cmake_minimum_required(VERSION 3.5.0)
project(SpectrumExample VERSION 1.0.0)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC SpectrumLib)