cmake_minimum_required(VERSION 3.18)
project(CPP_SPEED LANGUAGES CXX)

add_executable(demo main.cpp)

target_include_directories(demo PUBLIC
${PROJECT_SOURCE_DIR}/)