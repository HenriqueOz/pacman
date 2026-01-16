# PACMAN

This is a simple pacman clone made using SDL3 and some other dependencies by SDL, for images and fonts.

Initially my idea was to make a full pacman clone with ECS architecture. Eventually I just focused on the game logic and collision system.
There is only one ghost implemented, the red one (or Blinky, for those who know), and all the main mechanics are here.

If someday I have the interest in implementing the remaining ghosts I will touch the project again.

I reached my objective, by understanding how to make something without an engine, even if this is quite simple, it was really joyful to develop.

## Build

To build the project you will need a C/C++ compiler, CMake (>= 3.26) and Vcpkg.

Having all of these and after cloning the project. Do the following in the project's folder:

```bash
# On Windows
cmake --preset=windows-release
# On Linux
cmake --preset=linux-release
```

```bash
cmake --build build
```

The game will be in this path `./build/bin`. Copy its content to any folder you like.

---

<div align="center">
  <i>Made listening Anri and Meiko Nakahari</i>
</div>
