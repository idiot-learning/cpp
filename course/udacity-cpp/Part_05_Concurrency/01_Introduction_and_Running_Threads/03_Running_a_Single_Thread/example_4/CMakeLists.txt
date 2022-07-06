add_executable(example_4 example_4.cpp)
find_package(Threads)
target_link_libraries(example_4 ${CMAKE_THREAD_LIBS_INIT})