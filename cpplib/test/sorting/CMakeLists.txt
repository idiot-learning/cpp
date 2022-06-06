set(APP_NAME sorting)
add_executable(${APP_NAME} main.cpp )

target_include_directories(${APP_NAME} PUBLIC 
${PROJECT_SOURCE_DIR}/include/
)
