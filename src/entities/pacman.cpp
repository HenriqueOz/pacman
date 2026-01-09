#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_render.h>
#include <memory>

#include "config/config.hpp"
#include "game/collision_box.hpp"
#include "game/utils.hpp"
#include "pacman.hpp"

Pacman::Pacman(Vec2<float> position, SDL_Renderer * renderer, Input & input, CollisionManager & collision)
  : _input(input)
  , _collision(collision)
  , _position(position)
  , _direction{ 0, 0 }
{
    _sprite = std::make_unique<Sprite>(_position, renderer, config::assets::kPacmanIdleSprite);
    _bbox = std::make_unique<CollisionBox>(
      _collision, _position, Vec2<int>(config::tile::kTileWidth, config::tile::kTileHeight), CollisionTagBit::kPacman);
}

void
Pacman::update(float deltaTime)
{
    update_direction(_input);
    _position = wrap_position_by_size_around_screen(_position, _sprite->get_image_size());

    float hspd = 0.5 * _direction.x;
    float vspd = 0.5 * _direction.y;

    if (hspd != 0) {
        if (_collision.check_collision_at(
              { _position.x + hspd, _position.y }, _bbox->get_size(), get_collision_mask())) {
            hspd = 0;
        }
    }

    if (vspd != 0) {
        if (_collision.check_collision_at(
              { _position.x, _position.y + vspd }, _bbox->get_size(), get_collision_mask())) {
            vspd = 0;
        }
    }

    _position = { _position.x + hspd, _position.y + vspd };
    _sprite->position = _position;
    _collision.update_box_position(_bbox.get(), _position);
}

void
Pacman::render(SDL_Renderer * renderer)
{
    _sprite->render(renderer);
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

    Vec2<float> checkPos = { _position.x, _position.y };
    checkPos.x += newDirection.x;
    checkPos.y += newDirection.y;

    if (!_collision.check_collision_at(checkPos, _bbox->get_size(), get_collision_mask())) {
        _direction = newDirection;
    }
}
CollisionTagBitMask
Pacman::get_collision_mask() const
{
    return CollisionTagBit::kWall | CollisionTagBit::kGhostDoor;
}