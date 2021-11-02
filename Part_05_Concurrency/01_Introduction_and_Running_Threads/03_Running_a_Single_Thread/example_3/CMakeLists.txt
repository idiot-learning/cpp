add_executable(example_3 example_3.cpp)
find_package (Threads)
target_link_libraries (example_3 ${CMAKE_THREAD_LIBS_INIT})