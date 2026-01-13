# PACMAN

This a simple pacman clone made using SDL3 and some other depencies by SDL, for images and fonts.

Initially my idea was make a full pacman clone with ECS architecture. Eventually I just focused in the game logic and collision system.
There is only one ghost implemented, the red one (or Blinky, for those who know), and all the main mechanics are here.

If someday I have the interest in implement the reamining ghosts I will touch the project again.

I reached my objetive, by understand how to make something without an engine, even if this is quite simple, it was really joyful to develop.

## Build

To build the project you will need a C/C++ compiler, CMake (>= 3.26) and the Vcpkg

Having all of these and after cloninig the project. Run the following commands inside the project's folder:

```bash
cmake --preset=default
cmake --build build
```
