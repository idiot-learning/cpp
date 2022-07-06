find_library(SDL2_image_LIBRARY SDL2_image ${PROJECT_SOURCE_DIR}/thirdParty/SDL2_image-2.0.5/lib/x64)
add_library(SDL2_image STATIC IMPORTED GLOBAL) # GLOBAL -> if outside src tree
#message("The dnnbase library is: ${DNNBASE_LIBRARY}")
set_property(TARGET SDL2_image PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/third_party/SDL2_image-2.0.5/lib/x64)
set_property(TARGET SDL2_image APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/third_party/SDL2_image-2.0.5/include)