add_library(LED SHARED)
target_sources(LED
PUBLIC
led.cpp)
target_include_directories(LED 
PUBLIC
$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
#${CMAKE_SOURCE_DIR}/include
)
target_compile_definitions(LED PUBLIC SM_EXPORT)