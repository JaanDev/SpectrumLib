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

    set(EXAMPLES_OUT_DIR $<TARGET_FILE_DIR:${example_name}>)
    set(EXAMPLES_TARGET ${example_name})
endforeach()

add_custom_command(TARGET ${EXAMPLES_TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${EXAMPLES_OUT_DIR}/assets
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SpectrumLib> ${EXAMPLES_OUT_DIR}
)