cmake_minimum_required(VERSION 3.1)
project(SpectrumTest)

add_executable(SpectrumTest main.cpp)
target_link_libraries(SpectrumTest PUBLIC Spectrum)