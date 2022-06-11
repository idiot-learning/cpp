cmake_minimum_required(VERSION 3.18)
project(CPP_SPEED LANGUAGES CXX)

add_executable(demo main.cpp)


target_include_directories(demo PUBLIC
${PROJECT_SOURCE_DIR}/)

find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("${target_name} build with openmp")
    target_link_libraries(demo PRIVATE OpenMP::OpenMP_CXX)
endif()

