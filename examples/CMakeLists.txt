cmake_minimum_required(VERSION 3.5.0)
project(examples)

file(GLOB EXAMPLES
    *.cpp
)

foreach(example ${EXAMPLES})
    get_filename_component(example_name ${example} NAME_WE)
    message(STATUS "SPL: Found example ${example_name}")
    
    add_executable(${example_name} ${example})
    target_link_libraries(${example_name} PUBLIC SpectrumLib)
endforeach()