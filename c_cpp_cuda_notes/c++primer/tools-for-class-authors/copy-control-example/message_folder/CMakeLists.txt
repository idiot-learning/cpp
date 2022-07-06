add_library(message_folder SHARED)

target_include_directories(message_folder 
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(message_folder
PRIVATE
message.cpp
folder.cpp
)
