set(TARGET callback)

add_library(${TARGET})

target_include_directories(${TARGET} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_sources(${TARGET} PRIVATE
    ./callback.cpp
)
