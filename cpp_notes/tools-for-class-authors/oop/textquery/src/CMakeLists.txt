set(TARGET_NAME QueryBaseModule)

add_library(${TARGET_NAME} SHARED)

target_include_directories(${TARGET_NAME} 
PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_definitions(${TARGET_NAME}
PUBLIC
    $<$<BOOL:${WIN32}>:SM_EXPORT>
)

target_sources(${TARGET_NAME}
PUBLIC
    ./operator/query.cpp
    ./operator/andquery.cpp
    ./operator/queryresult.cpp
    ./textquery.cpp
)

