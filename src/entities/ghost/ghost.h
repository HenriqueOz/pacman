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
    Ghost(Vec2 const &pos, Vec2 const &scatter);
    ~Ghost() override {};
    EntityType getType() const override { return GHOST; };

    void update() override;
    void render(SDL_Renderer *renderer) const override;
    void setBestDirectionTo(Vec2 position);
    void drawLineToTarget(SDL_Renderer *renderer, Vec2 target) const;
    float getDotsDistance(Vec2 a, Vec2 b) const;
    float getManhattanDistance(Vec2 a, Vec2 b) const;
    Vec2 getTilePositionAt(Utils::Direction) const;
    void wrapOutOfBounds();
    int getDirectionPriority(Utils::Direction direction) const;
    void handleEatenState();
    void handleChasingState();
    void handleIdleState();
    void handleScatterState();

    std::vector<Utils::Direction> getAvailableDirections() const;

    Utils::Direction getBestDiretion() const;

  private:
    GhostStates m_state;
    GameController *m_gameController;
    Entities *m_entitiesRegistry;
    Vec2 m_currentTile;
    Vec2 m_spawnOrigin;
    Vec2 m_scatterTarget;
    Vec2 m_currentTarget;

    int m_speed;
    int m_eatenSpeed;
    int m_baseSpeed;
    int m_timer;
    int m_scatterTime;
    int m_chaseTime;

    Utils::Direction m_direction;
};

#endif