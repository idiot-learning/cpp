add_executable(quiz quiz.cpp)
find_package(Threads)
target_link_libraries(quiz ${CMAKE_THREAD_LIBS_INIT})