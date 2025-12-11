#include "SDL3/SDL_render.h"
#include "config/config.hpp"

#include "pellet.hpp"

void
Pellet::initialize(float x, float y, SDL_Renderer * renderer)
{
    _position = { x, y };

    _sprite.load(renderer, config::assets::kPelletIdleSprite);
    _sprite.size = _sprite.get_image_size();
    _sprite.position = { x + 8, y + 8 };
}

void
Pellet::render(SDL_Renderer * renderer) const
{
    _sprite.render(renderer);
}
