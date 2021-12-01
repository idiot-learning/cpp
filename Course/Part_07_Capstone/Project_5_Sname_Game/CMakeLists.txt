cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_subdirectory(third_party/SDL2_image-2.0.5)
#include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp src/gameMenu.cpp src/user.cpp)
target_include_directories(SnakeGame PUBLIC ${SDL2IMAGE_INCLUDE_DIR}  src)

target_link_libraries(SnakeGame PUBLIC SDL2_image ${SDL2_IMAGE_LIBRARIES})
