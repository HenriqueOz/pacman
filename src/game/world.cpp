#include <memory>
#include <vector>

#include "SDL3/SDL_render.h"

#include "config/config.hpp"
#include "entities/ghost.hpp"
#include "entities/pacman.hpp"
#include "entities/pellet.hpp"
#include "entities/wall.hpp"
#include "game/map.hpp"
#include "game/utils.hpp"

#include "game/world.hpp"

void
World::initialize(SDL_Renderer * renderer, Input & input, CollisionManager & collision)
{
    _gui = std::make_unique<Gui>(renderer);

    Vec2<int> tile{ 0, 0 };
    const MapMatrix & matrix = _map.get_map_matrix();
    Vec2<float> ghostExitPos{};

    for (const std::vector<MapTags> & row : matrix) {
        for (const MapTags tag : row) {
            const Vec2<float> position = tile_to_position(tile);

            switch (tag) {
                case MapTags::kPellet:
                    _pellets.push_back(std::make_unique<Pellet>(PelletType::kNormal, position, renderer, collision));
                    break;
                case MapTags::kSuperPellet:
                    _pellets.push_back(std::make_unique<Pellet>(PelletType::kSuper, position, renderer, collision));
                    break;
                case MapTags::kWall:
                    _walls.push_back(std::make_unique<Wall>(false, position, renderer, collision));
                    break;
                case MapTags::kGhostExit:
                    ghostExitPos = { position.x + config::tile::kTileWidth, position.y };
                    _walls.push_back(std::make_unique<Wall>(true, position, renderer, collision));
                    break;
                case MapTags::kPacmanSpawn: {
                    const Vec2<float> pacmanPosition =
                      Vec2<float>(position.x + config::tile::kTileWidth / 2.0f, position.y);
                    _pacman = std::make_unique<Pacman>(pacmanPosition, renderer, input, collision);
                    break;
                }
                case MapTags::kBlinkySpawn: {
                    const Vec2<float> blinkyPosition =
                      Vec2<float>(position.x + config::tile::kTileWidth / 2.0f, position.y);
                    _ghosts.push_back(
                      std::make_unique<Ghost>(GhostType::kBlinky, blinkyPosition, ghostExitPos, renderer, collision));
                    break;
                }
            }
            tile.x++;
        }
        tile.x = 0;
        tile.y++;
    }
}

void
World::reset(SDL_Renderer * renderer, Input & input, CollisionManager & collision)
{
    _gui.reset();
    _pacman.reset();
    _pellets.clear();
    _walls.clear();
    _ghosts.clear();

    _gameState = GameState();

    initialize(renderer, input, collision);
}

void
World::update(float deltaTime)
{
    _gameState.update();

    if (_gameState.has_ended()) {
        return;
    }

    bool allFoodsEaten = true;

    if (_pacman != nullptr)
        _pacman->update(deltaTime);

    for (const std::unique_ptr<Pellet> & pellet : _pellets) {
        pellet->update(deltaTime, _gameState);

        if (!pellet->is_eaten()) {
            allFoodsEaten = false;
        }
    }

    if (allFoodsEaten) {
        _gameState.set_state(State::kWin);
        return;
    }

    for (const std::unique_ptr<Ghost> & ghost : _ghosts) {
        ghost->update(deltaTime, _pacman->get_position(), _gameState);
    }
}

void
World::render(SDL_Renderer * renderer)
{
    for (const std::unique_ptr<Pellet> & pellet : _pellets) {
        pellet->render(renderer);
    }

    for (const std::unique_ptr<Ghost> & ghost : _ghosts) {
        ghost->render(renderer);
    }

    if (_pacman != nullptr)
        _pacman->render(renderer);

    for (const std::unique_ptr<Wall> & wall : _walls) {
        wall->render(renderer);
    }
}

void
World::renderGui(SDL_Renderer * renderer)
{
    if (_gui != nullptr) {
        _gui->render(renderer, _gameState);
    }
}
