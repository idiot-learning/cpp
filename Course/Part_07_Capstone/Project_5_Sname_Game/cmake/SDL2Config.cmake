
set(SDL2_image_URL "D:/SmartMore/learn/cpp/Course/Part_07_Capstone/Project_5_Sname_Game/third_party/SDL2_image-2.0.5")
#set(OpenCV_MD5 "41387503cbf07a706a28e629459e575b")



include(FetchContent)

FetchContent_Declare(SDL2
    URL ${SDL2_image_URL}

)

message(STATUS "Fetch OpenCV")
FetchContent_MakeAvailable(SDL2)
message(STATUS "Fetch OpenCV done")

FetchContent_GetProperties(SDL2 SOURCE_DIR SDL2_image_SOURCE_DIR)

# get OpenCV_DIR
set(SDL2_IMAGE_LIBRARIES ${SDL2_image_SOURCE_DIR}/third_party/SDL2_image-2.0.5/lib/x64)
set(SDL2_INCLUDE_DIRS ${SDL2_image_SOURCE_DIR}/third_party/SDL2_image-2.0.5/include)
