cmake_minimum_required(VERSION 3.13)

project(czerny_turner_visualizer)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules" ${CMAKE_MODULE_PATH})

add_subdirectory(corrade EXCLUDE_FROM_ALL)

list(APPEND CMAKE_PREFIX_PATH "C:/Users/Jesse Deuel/Documents/GitHub/Misc/SDL2-2.30.9")
set(MAGNUM_WITH_SDL2APPLICATION ON CACHE BOOL "" FORCE)
add_subdirectory(magnum EXCLUDE_FROM_ALL)

add_subdirectory(src)