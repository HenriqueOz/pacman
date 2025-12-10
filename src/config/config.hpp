#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include <string>

namespace config {

namespace assets {
const std::string kRoot = "./assets";
const std::string kMapCsv = assets::kRoot + "/map/map.csv";
const std::string kPacmanIdleSprite = assets::kRoot + "/sprites/test.png";
}

namespace tile {
constexpr std::uint32_t kHorizontalTiles = 28;
constexpr std::uint32_t kVerticalTiles = 31;
constexpr std::uint32_t kTileWidth = 16;
constexpr std::uint32_t kTileHeight = 16;
}

namespace window {
constexpr std::uint32_t kHorizontalScale = 1;
constexpr std::uint32_t kVerticalScale = 1;
constexpr std::uint32_t kWidth =
  (tile::kTileWidth * tile::kHorizontalTiles) * window::kHorizontalScale;
constexpr std::uint32_t kHeight =
  (tile::kTileHeight * tile::kVerticalTiles) * window::kVerticalScale;
constexpr const char * kTitle = "Pacman";
constexpr std::uint32_t kFps = 60;
constexpr std::uint32_t kFrameDelay = 1000 / window::kFps;
}

namespace gui {
constexpr std::uint32_t kTopHeight = 80;
constexpr std::uint32_t kBottomHeight = 50;
constexpr std::uint32_t kTotalHeight =
  window::kHeight + gui::kTopHeight + gui::kBottomHeight;
constexpr std::uint32_t kTotalWidth = window::kWidth;
}

}

#endif
