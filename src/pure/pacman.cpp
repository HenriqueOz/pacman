#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_render.h>

#include "config/config.hpp"
#include "game/input.hpp"
#include "pure/sprite.hpp"
#include "pacman.hpp"

void
Pacman::initialize(float x, float y, SDL_Renderer * renderer)
{
    _position = { x, y };
    _direction = { 0, 0 };

    _sprite.set_position(_position);
    _sprite.set_size({ 16, 16 });
    _sprite.load(renderer, config::assets::kPacmanIdleSprite);
}

void
Pacman::update(float deltaTime, Input & input)
{
    update_direction(input);

    _position.x += _speed * _direction.x * deltaTime;
    _position.y += _speed * _direction.y * deltaTime;

    _sprite.set_position(_position);
}

void
Pacman::render(SDL_Renderer * renderer)
{
    const SDL_FRect rect = { .x = _position.x,
                             .y = _position.y,
                             .w = config::tile::kTileWidth,
                             .h = config::tile::kTileHeight };

    _sprite.render(renderer);
}

void
Pacman::update_direction(Input & input)
{
    if (input.key_pressed(SDLK_LEFT))
        _direction = { -1, 0 };
    else if (input.key_pressed(SDLK_RIGHT))
        _direction = { 1, 0 };
    else if (input.key_pressed(SDLK_UP))
        _direction = { 0, -1 };
    else if (input.key_pressed(SDLK_DOWN))
        _direction = { 0, 1 };
}