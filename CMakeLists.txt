cmake_minimum_required(VERSION 3.26)

project(paman LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL3_DIR "C:/SDL/cmake/")

find_package(SDL3 CONFIG REQUIRED)

add_subdirectory(src)

