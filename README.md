# PACMAN

This is a simple pacman clone made using SDL3 and some other dependencies by SDL, for images and fonts.

Initially my idea was to make a full pacman clone with ECS architecture. Eventually I just focused on the game logic and collision system.
There is only one ghost implemented, the red one (or Blinky, for those who know), and all the main mechanics are here.

If someday I have the interest in implementing the remaining ghosts I will touch the project again.

I reached my objective, by understanding how to make something without an engine, even if this is quite simple, it was really joyful to develop.

## Build

To build the project you will need a C/C++ compiler, CMake (>= 3.26) and the Vcpkg

Having all of these and after cloning the project. Do the following in the project's folder:

In the project root, create the file: `CMakeUserPresets.json`

```json
{
  "version": 2,
  "configurePresets": [
    {
      "name": "release",
      "inherits": "vcpkg",
      "cacheVariables": {
        "VCPKG_ROOT": "\<Path to vcpkg\>",
        "CMAKE_BUILD_TYPE": "Release"
      }
    }
  ]
}
```

Then run the following commands

```bash
cmake --preset=release
cmake --build build
```

The game will be in this path `./build/bin`. Copy its content to any place you like, just remember to put everything inside a folder
