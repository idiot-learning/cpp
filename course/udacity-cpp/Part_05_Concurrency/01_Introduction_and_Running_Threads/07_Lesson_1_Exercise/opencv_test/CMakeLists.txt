cmake_minimum_required(VERSION 3.18)
project(TEST_CMAKE)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
message("OpenCV_INCLUDE_DIRS is : ${OpenCV_INCLUDE_DIRS}")
add_executable(main main.cpp)
message("OpenCV_LIBS is : ${OpenCV_LIBS}")
target_link_libraries(main ${OpenCV_LIBS})