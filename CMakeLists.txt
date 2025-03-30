cmake_minimum_required(VERSION 3.26)

project(pacman LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL3_DIR "C:/SDL/cmake/")
set(SDL3_ttf_DIR "C:/SDL3_ttf-3.2.0/cmake")

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

set(link_assets ${CMAKE_SOURCE_DIR}/assets)

add_subdirectory(src)

