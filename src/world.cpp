#include <cstddef>

#include "world.hpp"
#include "game/input.hpp"
#include "pure/pacman.hpp"
#include "config/config.hpp"

void
World::initialize(SDL_Renderer * renderer)
{
    _pellets.reserve(50);

    for (std::size_t i = 0; i < _pellets.size(); i++) {
        _pellets.push_back(Pellet());
    }

    int pelletX = 0;
    int pelletY = 0;

    for (const Pellet & pellet : _pellets) {
        pelletX += config::tile::kTileWidth;
        pelletX += config::tile::kTileHeight;
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
    _pacman.render(renderer);
}

void
World::renderGui(SDL_Renderer * renderer)
{
}
