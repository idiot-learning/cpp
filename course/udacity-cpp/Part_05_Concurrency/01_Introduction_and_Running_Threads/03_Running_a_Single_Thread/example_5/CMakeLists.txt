add_executable(example_5 example_5.cpp)
find_package(Threads)
target_link_libraries(example_5 ${CMAKE_THREAD_LIBS_INIT})