cmake_minimum_required(VERSION 3.11.3)

# set(CMAKE_CXX_STANDARD 17)
project(OSM_A_star_search)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake  )
set(OpenCV_DIR "/home/wangchao/Downloads/opencv-4.2.0/build")
find_package(OpenCV 4.2 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
message("include opencv directory is${OpenCV_INCLUDE_DIRS}")
#link_directories(${OpenCV_LIBS})
message("linked opencv directory is${OpenCV_LIBS}")
add_definitions(${OpenCV_DEFINITIONS})

# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

# Add project executable
add_executable(traffic_simulation ${project_SRCS})
target_link_libraries(traffic_simulation ${OpenCV_LIBS})
