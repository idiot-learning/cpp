add_executable(example_6 example_6.cpp)
find_package(Threads)
target_link_libraries(example_6 ${CMAKE_THREAD_LIBS_INIT})