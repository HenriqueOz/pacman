#include "collision_box.hpp"

CollisionBox::CollisionBox(const Vec2<float> position,
                           const Vec2<int> size,
                           const CollisionTag tag)
  : position(position)
  , tag(tag)
  , size(size)
{
}

void
CollisionBox::render(SDL_Renderer * renderer, SDL_Color && color) const
{
    const SDL_FRect rect = { .x = position.x,
                             .y = position.y,
                             .w = static_cast<float>(size.x),
                             .h = static_cast<float>(size.y) };

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 10);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
