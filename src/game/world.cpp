#include <cstddef>

#include "game/world.hpp"
#include "game/input.hpp"
#include "pure/pacman.hpp"
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

        _pellets[i].initialize(pelletX, pelletY, renderer);
        col++;
    }

    _pacman.initialize(10.f, 10.f, renderer);
}

void
World::update(float deltaTime, Input & input)
{
    _pacman.update(deltaTime, input);
}

void
World::render(SDL_Renderer * renderer)
{
    for (const Pellet & pellet : _pellets) {
        pellet.render(renderer);
    }
    _pacman.render(renderer);
}

void
World::renderGui(SDL_Renderer * renderer)
{
}
