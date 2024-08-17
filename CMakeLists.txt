cmake_minimum_required(VERSION 3.20)

set(CMAKE_BUILD_TYPE Debug)

# Be sure it is built as Release Mode
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_COMPILER /usr/bin/clang++)
#set(CMAKE_C_COMPILER /usr/bin/clang)
set(FETCHCONTENT_UPDATES_DICONNECTED ON)

project(sdl-demo LANGUAGES CXX)

add_subdirectory(3rd/SDL       EXCLUDE_FROM_ALL)
add_subdirectory(3rd/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(src/utils)

add_executable(demo src/main.cc)
target_include_directories(
    demo PUBLIC
    3rd/SDL/include
    3rd/SDL_image/include
)

target_link_libraries(
    demo PUBLIC
    SDL2::SDL2
    SDL2_image
    utils
)
