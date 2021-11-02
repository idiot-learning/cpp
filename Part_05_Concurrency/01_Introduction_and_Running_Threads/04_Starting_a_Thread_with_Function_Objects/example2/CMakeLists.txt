add_executable(example2 example_2.cpp)

find_package(Threads)
target_link_libraries(example2 ${CMAKE_THREAD_LIBS_INIT})