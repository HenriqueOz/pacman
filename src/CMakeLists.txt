cmake_minimum_required(VERSION 3.26)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB SRC_FILES *.cpp)
file(GLOB HEADER_FILES *.h)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} SDL3::SDL3 SDL3_ttf::SDL3_ttf)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND $(CMAKE_COMMAND)
        -E create_symlink ${link_assets} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND}
    -E copy -t $<TARGET_FILE_DIR:${PROJECT_NAME}> $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
  COMMAND_EXPAND_LISTS
)