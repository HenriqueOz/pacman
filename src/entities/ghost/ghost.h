#ifndef _GHOST_H
#define _GHOST_H

#include "entities/utils/utils.h"
#include "game/controller/game_controller.h"
#include "game/entities/entities.h"
#include "game/input/input_manager.h"
#include "vec/vec.h"
#include <SDL3/SDL_pixels.h>
#include <entities/entity.h>
#include <vector>

enum class GhostStates
{
    SPAWN,
    IDLE,
    SCATTER,
    CHASING,
    FRIGHTENED,
    EATEN,
};

enum class GhostType
{
    Blinky,
    Pinky,
    Inky,
    Clyde
};

class Ghost : public Entity
{
  public:
    Ghost(Vec2 const &pos,
          Vec2 const &scatter,
          GhostType type,
          int startDelay,
          GameController *gameController,
          Entities *entitiesRegistry,
          InputManager *inputManager);
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
    Vec2 getPinkyChasingTarget(Vec2 pacmanPosition, Utils::Direction pacmanDirection) const;
    Vec2 getInkyChasingTarget(Vec2 pacmanPosition, Utils::Direction pacmanDirection) const;
    Vec2 getClydeChasingTarget(Vec2 pacmanPosition, Utils::Direction pacmanDirection) const;
    Utils::Direction getReverseDirection(Utils::Direction direction) const;

    SDL_Color getGhostColor() const;
    Vec2 getGhostChaseTarget() const;

    std::vector<Utils::Direction> getAvailableDirections() const;

    Utils::Direction getBestDiretion() const;

  private:
    GhostStates m_state;
    GameController *m_gameController;
    Entities *m_entitiesRegistry;
    InputManager *m_inputManager;
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
    int m_startDelay;

    GhostType m_ghostType;

    Utils::Direction m_direction;
};

#endif