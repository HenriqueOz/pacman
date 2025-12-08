#ifndef PURE_H_
#define PURE_H_

#include <iostream>
#include <memory>

#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_render.h"

#include "game/input.hpp"
#include "pacman.hpp"

static Vec2<int>
update_direction(Input & input, Pacman * pacman)
{
    Vec2<int> newDirection = pacman->direction;

    if (input.key_pressed(SDLK_LEFT))
        return newDirection = { -1, 0 };
    else if (input.key_pressed(SDLK_RIGHT))
        return newDirection = { 1, 0 };
    else if (input.key_pressed(SDLK_UP))
        return newDirection = { 0, -1 };
    if (input.key_pressed(SDLK_DOWN))
        return newDirection = { 0, 1 };

    return newDirection;
}

std::unique_ptr<Pacman>
create_pacman(float x, float y)
{
    Pacman p{ .position = { x, y } };
    return std::make_unique<Pacman>(p);
}

void
update_pacman(float deltaTime, Input & input, Pacman * pacman)
{
    pacman->direction = update_direction(input, pacman);

    const float speed = 60.f;

    pacman->position.x += speed * pacman->direction.x * deltaTime;
    pacman->position.y += speed * pacman->direction.y * deltaTime;

    std::cout << "x: " << pacman->position.x << " y: " << pacman->position.y
              << "\n";
}

void
render_pacman(SDL_Renderer * renderer, Pacman * pacman)
{
    const Vec2<float> & position = pacman->position;
    const SDL_FRect rect = {
        .x = position.x, .y = position.y, .w = 16, .h = 16
    };

    SDL_SetRenderDrawColorFloat(renderer, 1.f, 1.f, 1.f, 1.f);
    SDL_RenderRect(renderer, &rect);
    SDL_SetRenderDrawColorFloat(renderer, 0.f, 0.f, 0.f, 1.f);
}
#endif