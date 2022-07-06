add_executable(example4 example_4.cpp)
find_package(Threads)
target_link_libraries(example4 ${CMAKE_THREAD_LIBS_INIT})