cmake_minimum_required(VERSION 3.26)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
  components/
  game/
  pacman/
)

target_sources(${PROJECT_NAME} PRIVATE
  main.cpp
  game/game.cpp
  game/time.cpp
  components/registry.cpp
  components/entity.cpp
  components/sprite_component.cpp
  pacman/pacman.h
)

target_sources(${PROJECT_NAME} PRIVATE
  main.h
  game/game.h
  game/time.h
  components/registry.h
  components/entity.h
  components/sprite_component.h
  pacman/pacman.cpp
)


target_link_libraries(${PROJECT_NAME} SDL3::SDL3 SDL3_ttf::SDL3_ttf)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${PROJECT_NAME}> $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
  COMMAND_EXPAND_LISTS
)