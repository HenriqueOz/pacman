#ifndef PACMAN_H_
#define PACMAN_H_

#include <memory>

#include "SDL3/SDL_render.h"

#include "game/input.hpp"
#include "utils.hpp"

struct Pacman
{
    Vec2<float> position;
    Vec2<int> direction;
};

extern std::unique_ptr<Pacman>
create_pacman(float x, float y);

extern void
update_pacman(float deltaTime, Input & input, Pacman * pacman);

extern void
render_pacman(SDL_Renderer * renderer, Pacman * pacman);

#endif