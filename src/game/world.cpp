#include <cstddef>

#include "game/world.hpp"
#include "config/config.hpp"

void
World::initialize(SDL_Renderer * renderer)
{
    _pellets.resize(50);

    int pelletX = 0;
    int pelletY = 0;
    int row = 0;
    int col = 0;

    for (std::size_t i = 0; i < _pellets.size(); i++) {
        if (i == config::tile::kHorizontalTiles) {
            col = 0;
            row++;
        }

        pelletX = config::tile::kTileWidth * col;
        pelletY = config::tile::kTileHeight * row;

        _pellets[i] = std::make_unique<Pellet>(pelletX, pelletY, renderer);
        col++;
    }

    _pacman = std::make_unique<Pacman>(10, 10, renderer);
}

void
World::update(float deltaTime, Input & input, CollisionManager & collision)
{
    _pacman->update(deltaTime, input, collision);
}

void
World::render(SDL_Renderer * renderer)
{
    for (const std::unique_ptr<Pellet> & pellet : _pellets) {
        pellet->render(renderer);
    }
    _pacman->render(renderer);
}

void
World::renderGui(SDL_Renderer * renderer)
{
}
