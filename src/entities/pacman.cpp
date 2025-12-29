#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_render.h>

#include "config/config.hpp"
#include "pacman.hpp"

Pacman::Pacman(float x, float y, SDL_Renderer * renderer, Input & input, CollisionManager & collision)
  : _input(input)
  , _collision(collision)
  , _position{ x, y }
  , _direction{ 1, 0 }
  , _sprite(_position, _size, renderer, config::assets::kPacmanIdleSprite)
  , _bbox(_position, _size, CollisionTag::pacman)
{
    collision.register_box(&_bbox);
}

void
Pacman::update(float deltaTime)
{
    update_direction(_input);
    wrap_around_screen();

    const Vec2<float> oldPosition = _position;

    const float newX = _position.x + _speed * static_cast<float>(_direction.x) * deltaTime;
    const float newY = _position.y + _speed * static_cast<float>(_direction.y) * deltaTime;

    // if (_collision.check_collision_at({ newX, _position.y }, _size, CollisionTag::wall)) {
    //     while (std::abs(_position.x - oldPosition.x) > 0.1f) {
    //         _position.x += (_position.x < oldPosition.x) ? 0.1f : -0.1f;
    //     }
    // }

    // if (_collision.check_collision_at({ _position.x, newY }, _size, CollisionTag::wall)) {
    //     while (std::abs(_position.y - oldPosition.y) > 0.1f) {
    //         _position.y += (_position.y < oldPosition.y) ? 0.1f : -0.1f;
    //     }
    // }

    _sprite.position = _position;
    _collision.update_box_position(&_bbox, _position);
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
    Vec2<int> newDirection = _direction;

    if (input.key_pressed(SDLK_LEFT))
        newDirection = { -1, 0 };
    else if (input.key_pressed(SDLK_RIGHT))
        newDirection = { 1, 0 };
    else if (input.key_pressed(SDLK_UP))
        newDirection = { 0, -1 };
    else if (input.key_pressed(SDLK_DOWN))
        newDirection = { 0, 1 };

    Vec2<float> checkPos = _position;
    checkPos.x += static_cast<float>(newDirection.x);
    checkPos.y += static_cast<float>(newDirection.y);

    if (!_collision.check_collision_at(checkPos, _size, CollisionTag::wall)) {
        _direction = newDirection;
    }
}

void
Pacman::wrap_around_screen()
{
    if (_position.x + _size.x < 0) {
        _position.x = static_cast<float>(config::view::kGameTextureWidth);
    } else if (_position.x > static_cast<float>(config::view::kGameTextureWidth)) {
        _position.x = -_size.x;
    }

    if (_position.y + _size.y < 0) {
        _position.y = static_cast<float>(config::view::kGameTextureHeight);
    } else if (_position.y > static_cast<float>(config::view::kGameTextureHeight)) {
        _position.y = -_size.y;
    }
}
