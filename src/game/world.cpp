#include <cstddef>

#include "SDL3/SDL_render.h"

#include "game/world.hpp"
#include "config/config.hpp"

void
World::initialize(SDL_Renderer * renderer, Input & input, CollisionManager & collision)
{
    // for (std::size_t i = 0; i < config::tile::kHorizontalTiles; i++) {
    //     _walls.push_back(std::make_unique<Wall>(i * config::tile::kTileWidth, 0, renderer, collision));
    //     _walls.push_back(std::make_unique<Wall>(i * config::tile::kTileWidth,
    //                                             (config::tile::kVerticalTiles - 1) * config::tile::kTileHeight,
    //                                             renderer,
    //                                             collision));
    // }

    _walls.push_back(std::make_unique<Wall>(
      config::view::kGameTextureWidth / 2, config::view::kGameTextureHeight / 2, renderer, collision));
    _walls.push_back(std::make_unique<Wall>(config::view::kGameTextureWidth / 2 - config::tile::kTileWidth * 2,
                                            config::view::kGameTextureHeight / 2,
                                            renderer,
                                            collision));
    _walls.push_back(std::make_unique<Wall>(config::view::kGameTextureWidth / 2 - config::tile::kTileWidth,
                                            config::view::kGameTextureHeight / 2 - config::tile::kTileHeight,
                                            renderer,
                                            collision));

    _pacman = std::make_unique<Pacman>(10, 10, renderer, input, collision);
}

void
World::update(float deltaTime)
{
    _pacman->update(deltaTime);

    for (const std::unique_ptr<Pellet> & pellet : _pellets) {
        pellet->update(deltaTime);
    }
}

void
World::render(SDL_Renderer * renderer)
{
    _pacman->render(renderer);

    for (const std::unique_ptr<Pellet> & pellet : _pellets) {
        pellet->render(renderer);
    }

    for (const std::unique_ptr<Wall> & wall : _walls) {
        wall->render(renderer);
    }
}

void
World::renderGui(SDL_Renderer * renderer)
{
}
