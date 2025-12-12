#include "SDL3/SDL_render.h"
#include "config/config.hpp"

#include "pellet.hpp"

Pellet::Pellet(float x, float y, SDL_Renderer * renderer)
  : _position{ x, y }
  , _sprite({ x + 8, y + 8 },
            { 8, 8 },
            renderer,
            config::assets::kPelletIdleSprite)
{
}

void
Pellet::render(SDL_Renderer * renderer) const
{
    _sprite.render(renderer);
}
