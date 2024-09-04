file(GLOB_RECURSE OBJECT_SOURCE src/*.cc include/*.h)

add_library(object SHARED ${OBJECT_SOURCE})

target_include_directories(
    object PUBLIC
    include
    ../../3rd/SDL/include
    ../../3rd/SDL_image/include
)

target_link_libraries(
    object PUBLIC
    SDL2::SDL2
    SDL2_image
)
