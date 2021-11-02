cmake_minimum_required(VERSION 3.18)
project(strblob_v1)

set(SRC ${CMAKE_SOURCE_DIR}/src/StrBlob.cpp)
add_executable(demo ${SRC})