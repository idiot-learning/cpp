add_executable(example1 example_1.cpp)

find_package(Threads)
target_link_libraries(example1 ${CMAKE_THREAD_LIBS_INIT})