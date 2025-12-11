#include "collision_box.hpp"

CollisionBox::CollisionBox(const Vec2<float> position,
                           const Vec2<int> size,
                           const Tag tag)
  : _oldPosition(position)
  , _position(position)
  , _tag(tag)
  , size(size)
{
}

void
CollisionBox::render(SDL_Renderer * renderer, SDL_Color && color) const
{
    const SDL_FRect rect = { .x = _position.x,
                             .y = _position.y,
                             .w = static_cast<float>(size.x),
                             .h = static_cast<float>(size.y) };

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 127);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
