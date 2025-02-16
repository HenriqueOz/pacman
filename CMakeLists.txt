cmake_minimum_required(VERSION 3.26)

include(FetchContent)

project(pacman LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(link_assets ${CMAKE_SOURCE_DIR}/assets)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.26
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
    SDL3_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-3.2.2
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(SDL3_ttf)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} SDL3::SDL3 SDL3_ttf::SDL3_ttf)

add_subdirectory(src)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
        ${SRC_FILES}
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -E create_symlink ${link_assets} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  -E copy -t $<TARGET_FILE_DIR:${PROJECT_NAME}> $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
  COMMAND_EXPAND_LISTS
)
