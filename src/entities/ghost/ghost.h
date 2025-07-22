#ifndef _GHOST_H
#define _GHOST_H

#include "entities/utils/utils.h"
#include "registry/controller/game_controller.h"
#include "registry/entities/entities.h"
#include "vec/vec.h"
#include <entities/entity.h>
#include <vector>

enum class GhostStates
{
    IDLE,
    SCATTER,
    CHASING,
    FRIGHTENED,
    EATEN,
};

class Ghost : public Entity
{
  public:
    Ghost(Vec2 const &pos);
    ~Ghost() override {};
    EntityType getType() const override { return GHOST; };

    void update() override;
    void render(SDL_Renderer *renderer) const override;
    void setBestDirectionTo(Vec2 position);
    void drawTriangleToTarget(SDL_Renderer *renderer, Vec2 target) const;
    void exitSpawn();
    float getDotsDistance(Vec2 a, Vec2 b) const;
    float getManhattanDistance(Vec2 a, Vec2 b) const;
    Vec2 getTilePositionAt(Utils::Direction) const;
    void wrapOutOfBounds();

    std::vector<Utils::Direction> getAvailableDirections() const;

    Utils::Direction getBestDiretion() const;

  private:
    GhostStates m_state;
    GameController *m_gameController;
    Entities *m_entitiesRegistry;
    Vec2 m_currentTile;
    Vec2 m_spawnOrigin;

    int m_speed;

    Utils::Direction m_direction;
};

#endif