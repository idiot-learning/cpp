cmake_minimum_required(VERSION 3.18)
project(CPP_SPEED LANGUAGES CXX)

add_executable(demo main.cpp)
add_compile_options(O3)

target_include_directories(demo PUBLIC
${PROJECT_SOURCE_DIR}/)

# find_package(OpenMP REQUIRED)
# if(OPENMP_FOUND)
#     message("${target_name} build with openmp")
#     target_link_libraries(demo PRIVATE OpenMP::OpenMP_CXX)
# endif()
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(demo PUBLIC Threads::Threads)