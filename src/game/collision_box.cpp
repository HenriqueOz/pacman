#include "collision_box.hpp"

CollisionBox::CollisionBox(const Vec2<float> position, const Vec2<int> size, const CollisionTagBit tag)
  : position(position)
  , _tag(tag)
  , _size(size)
{
}

void
CollisionBox::render(SDL_Renderer * renderer, SDL_Color && color) const
{
    const SDL_FRect rect = { position.x, position.y, static_cast<float>(_size.x), static_cast<float>(_size.y) };

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 63);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
