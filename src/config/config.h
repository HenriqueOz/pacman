#ifndef CONFIG_H_
#define CONFIG_H_

#include <SDL3/SDL_stdinc.h>
#include <string>

namespace Config {
const std::string assetsPath = "assets";
const std::string mapFilePath = assetsPath + "/map.csv";
const char *const windowName = "Pacman";

const unsigned horizontalTiles = 28;
const unsigned verticalTiles = 31;
const unsigned tileWidth = 16;
const unsigned tileHeight = 16;
const unsigned horizontalScale = 1;
const unsigned verticalScale = 1;
const unsigned bottomGuiHeight = 100;

const unsigned windowWidth = tileWidth * horizontalTiles * horizontalScale;
const unsigned windowHeight = tileHeight * verticalTiles * horizontalScale + bottomGuiHeight;
const unsigned logicalWidth = tileWidth * horizontalTiles;
const unsigned logicalHeight = tileHeight * verticalTiles;
const float aspectRatio = (float)windowWidth / windowHeight;

const Uint16 fps = 60;
const Uint16 frameDelay = 1000 / fps;
}

#endif