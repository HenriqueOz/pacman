#include "SDL3/SDL_render.h"
#include "game/map.hpp"
#include "game/utils.hpp"
#include <memory>
#include <vector>

#include "game/world.hpp"

void
World::initialize(SDL_Renderer * renderer, Input & input, CollisionManager & collision)
{
    Vec2<int> tile{ 0, 0 };
    const MapMatrix & matrix = _map.get_map_matrix();

    for (const std::vector<MapTags> & row : matrix) {
        for (const MapTags tag : row) {
            const Vec2<float> position = tile_to_position(tile);

            switch (tag) {
                case kEmpty:
                    break;
                case kPellet:
                    _pellets.push_back(std::make_unique<Pellet>(position, renderer, collision));
                    break;
                case kWall:
                    _walls.push_back(std::make_unique<Wall>(position, renderer, collision));
                    break;
                case kPacmanSpawn:
                    _pacman = std::make_unique<Pacman>(position, renderer, input, collision);
                    break;
            }
            tile.x++;
        }
        tile.x = 0;
        tile.y++;
    }
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
