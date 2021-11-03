cmake_minimum_required(VERSION 3.18)
project(reference_wrapper)

add_subdirectory(src)

add_executable(main main.cpp)

target_link_libraries(main 
PUBLIC LED
)

set_target_properties(main PROPERTIES CXX_STANDARD 17)