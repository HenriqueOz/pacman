#include "SDL3/SDL_render.h"

#include "config/config.hpp"
#include "game/collision_box.hpp"
#include "game/utils.hpp"
#include <filesystem>
#include <memory>
#include "pellet.hpp"

Pellet::Pellet(PelletType type, Vec2<float> position, SDL_Renderer * renderer, CollisionManager & collision)
  : _collision(collision)
  , _position(position)
  , _type(type)
{
    const Vec2<float> bboxPosition = { _position.x + config::tile::kTileWidth / 2.0f,
                                       _position.y + config::tile::kTileHeight / 2.0f };
    const Vec2<int> bboxSize = { config::tile::kTileWidth / 4, config::tile::kTileHeight / 4 };

    _bbox = std::make_unique<CollisionBox>(_collision, bboxPosition, bboxSize, CollisionTagBit::kPellet);
    _sprite = std::make_unique<Sprite>(_position, renderer, get_sprite_path());
}

Pellet::~Pellet() {}

void
Pellet::update(float deltaTime, GameState & gameState)
{
    if (_eaten) {
        return;
    }

    if (_collision.check_collision_at(
          _bbox->position, _bbox->get_size(), static_cast<CollisionTagBitMask>(CollisionTagBit::kPacman))) {
        handle_eaten_event(gameState);
    };
}

void
Pellet::render(SDL_Renderer * renderer) const
{
    if (_eaten) {
        return;
    }
    _sprite->render(renderer);
}

std::filesystem::path
Pellet::get_sprite_path() const
{
    switch (_type) {
        case kNormal:
            return config::assets::kPelletIdleSprite;
        case kSuper:
            return config::assets::kSuperPelletIdleSprite;
        case kFruit:
            return config::assets::kPelletIdleSprite;
            break;
    }
}

void
Pellet::handle_eaten_event(GameState & gameState)
{
    _eaten = true;

    gameState.add_points(_value);

    if (_type == PelletType::kSuper) {
        gameState.set_ghosts_frightened();
    }
}
