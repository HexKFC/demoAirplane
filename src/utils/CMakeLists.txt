file(GLOB_RECURSE UTILS_SOURCE src/*.cc include/*.h)

add_library(utils SHARED ${UTILS_SOURCE})

target_include_directories(
    utils PUBLIC
    include
    ../../3rd/SDL/include
    # ../../3rd/SDL_image/include
)

target_link_libraries(
    utils PUBLIC
    SDL2::SDL2
    # SDL2_image
)
