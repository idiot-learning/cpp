cmake_minimum_required(VERSION 3.16 )

project(test_file_output VERSION 0.1.0 LANGUAGES CXX)

add_executable(test_filestream )

target_sources(test_filestream 
PUBLIC
    main.cpp
    modbus.cpp
)
