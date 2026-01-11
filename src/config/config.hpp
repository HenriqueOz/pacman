#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include <filesystem>

namespace config {

namespace assets {
const std::filesystem::path kRoot{ "assets" };
const std::filesystem::path kMapCsv = assets::kRoot / "map/map.csv";

const std::filesystem::path kSpritesRoot = assets::kRoot / "sprites";
const std::filesystem::path kPacmanIdleSprite = assets::kSpritesRoot / "pacman.png";
const std::filesystem::path kBlinkyIdleSprite = assets::kSpritesRoot / "blinky.png";
const std::filesystem::path kFrightenedIdleSprite = assets::kSpritesRoot / "frightened.png";
const std::filesystem::path kEatenIdleSprite = assets::kSpritesRoot / "eaten.png";
const std::filesystem::path kPelletIdleSprite = assets::kSpritesRoot / "pellet.png";
const std::filesystem::path kSuperPelletIdleSprite = assets::kSpritesRoot / "super_pellet.png";
const std::filesystem::path kWallIdleSprite = assets::kSpritesRoot / "wall.png";
}

namespace tile {
constexpr std::uint32_t kHorizontalTiles = 28;
constexpr std::uint32_t kVerticalTiles = 31;
constexpr std::uint32_t kTileWidth = 8;
constexpr std::uint32_t kTileHeight = 8;
}

namespace view {
constexpr std::uint32_t kGuiTopHeight = tile::kTileHeight * 4;
constexpr std::uint32_t kGuiBottomHeight = tile::kTileHeight * 4;
constexpr std::uint32_t kGameTextureWidth = tile::kTileWidth * tile::kHorizontalTiles;
constexpr std::uint32_t kGameTextureHeight = tile::kTileHeight * tile::kVerticalTiles;
constexpr std::uint32_t kSurfaceHeight = kGuiTopHeight + kGameTextureHeight + kGuiBottomHeight;
constexpr std::uint32_t kSurfaceWidth = view::kGameTextureWidth;
}

namespace window {
constexpr std::uint32_t kHorizontalScale = 3;
constexpr std::uint32_t kVerticalScale = 3;
constexpr std::uint32_t kWidth = view::kSurfaceWidth * window::kHorizontalScale;
constexpr std::uint32_t kHeight = view::kSurfaceHeight * window::kVerticalScale;
constexpr const char * kTitle = "Pacman";
constexpr std::uint32_t kFps = 60;
constexpr std::uint32_t kFrameDelay = 1000 / window::kFps;
}

}

#endif
