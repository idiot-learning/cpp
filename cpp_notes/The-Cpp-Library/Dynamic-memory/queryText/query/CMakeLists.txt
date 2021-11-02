add_library(query STATIC
    src/TextQuery.cpp
)
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS True)
endif()

target_include_directories(query
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(query PUBLIC cxx_std_14)