#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>

namespace config {

namespace window {
constexpr std::uint32_t HORIZONTAL_TILES = 28;
constexpr std::uint32_t VERTICAL_TILES = 31;
constexpr std::uint32_t TILE_WIDTH = 16;
constexpr std::uint32_t TILE_HEIGHT = 16;
constexpr std::uint32_t HORIZONTAL_SCALE = 1;
constexpr std::uint32_t VERTICAL_SCALE = 1;
constexpr std::uint32_t WIDTH = (TILE_WIDTH * HORIZONTAL_TILES) * HORIZONTAL_SCALE;
constexpr std::uint32_t HEIGHT = (TILE_HEIGHT * VERTICAL_TILES) * VERTICAL_SCALE;
constexpr const char * TITLE = "Pacman";
constexpr std::uint32_t FPS = 60;
constexpr std::uint32_t FRAME_DELAY = 1000 / FPS;
}

namespace gui {
constexpr std::uint32_t TOP_HEIGHT = 80;
constexpr std::uint32_t BOTTOM_HEIGHT = 50;
constexpr std::uint32_t TOTAL_HEIGHT = window::HEIGHT + TOP_HEIGHT + BOTTOM_HEIGHT;
constexpr std::uint32_t TOTAL_WIDTH = window::WIDTH;
}

}

#endif
