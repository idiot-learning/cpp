cmake_minimum_required(VERSION 3.18 )

project(Query)
set(CMAKE_CXX_STANDARD 17)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/)

add_compile_options(
    $<$<OR:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>:/utf-8>
)
add_subdirectory(src)
add_subdirectory(example)
