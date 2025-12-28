#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_render.h>

#include "config/config.hpp"
#include "pacman.hpp"

Pacman::Pacman(float x,
               float y,
               SDL_Renderer * renderer,
               Input & input,
               CollisionManager & collision)
  : _input(input)
  , _collision(collision)
  , _position{ x, y }
  , _direction{ 1, 0 }
  , _sprite(_position, { 16, 16 }, renderer, config::assets::kPacmanIdleSprite)
  , _bbox(_position, { 16, 16 }, CollisionTag::pacman)
{
}

void
Pacman::update(float deltaTime)
{
    update_direction(_input);

    _position.x += _speed * _direction.x * deltaTime;
    _position.y += _speed * _direction.y * deltaTime;

    _sprite.position = _position;

    _bbox.position = _position;
    _collision.register_box(&_bbox);
}

void
Pacman::render(SDL_Renderer * renderer)
{
    _sprite.render(renderer);
    _bbox.render(renderer, SDL_Color{ 255, 0, 0, 255 });
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
