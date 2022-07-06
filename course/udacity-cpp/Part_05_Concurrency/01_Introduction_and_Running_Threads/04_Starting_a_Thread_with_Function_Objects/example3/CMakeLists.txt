add_executable(example3 example_3.cpp)
find_package(Threads)
target_link_libraries(example3 ${CMAKE_THREAD_LIBS_INIT})