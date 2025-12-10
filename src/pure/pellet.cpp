#include "pellet.hpp"
#include "SDL3/SDL_render.h"

void
Pellet::initialize(float x, float y, SDL_Renderer * renderer)
{
    _position = { x, y };
}

void
Pellet::render(SDL_Renderer * renderer)
{
    const SDL_FRect rect = {
        .x = _position.x, .y = _position.y, .w = 8, .h = 8
    };

    SDL_SetRenderDrawColorFloat(renderer, 1.f, 1.f, 1.f, 1.f);
}