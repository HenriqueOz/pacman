#include "food.h"
#include "config/config.h"
#include "vec/vec.h"

Food::Food(Vec2 const &pos)
{
    m_size.update({ 4, 4 });
    m_position.update({
      static_cast<int>(pos.x + (Config::tileWidth / 2) - (m_size.x / 2)),
      static_cast<int>(pos.y + (Config::tileHeight / 2) - (m_size.y / 2)),
    });
}

void
Food::update()
{
}

void
Food::render(SDL_Renderer *renderer) const
{
    SDL_FRect rect = { static_cast<float>(m_position.x),
                       static_cast<float>(m_position.y),
                       static_cast<float>(m_size.x),
                       static_cast<float>(m_size.y) };

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}