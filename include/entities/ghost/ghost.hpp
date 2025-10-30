#ifndef _GHOST_HPP
#define _GHOST_HPP

#include "entities/utils/movement.hpp"
#include "game/controller/game_controller.hpp"
#include "game/entities/entities.hpp"
#include "game/input/input_manager.hpp"
#include "vec/vec.hpp"
#include <SDL3/SDL_pixels.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <entities/entity.hpp>
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
    Ghost(Vec2 const & pos,
          Vec2 const & scatter,
          GhostType type,
          int startDelay,
          GameController * gameController,
          Entities * entitiesRegistry,
          InputManager * inputManager);
    ~Ghost() override {};

    void update() override;
    void render(SDL_Renderer * renderer, TTF_TextEngine * textEngine) const override;
    EntityType getType() const override { return GHOST; };

    void drawLineToTarget(SDL_Renderer * renderer, Vec2 target) const;
    void drawClydeCircle(SDL_Renderer * renderer) const;
    SDL_Color getGhostColor() const;
    Vec2 getGhostChaseTarget() const;

    void setBestDirectionTo(Vec2 position);
    int getDirectionPriority(Utils::Direction direction) const;
    std::vector<Utils::Direction> getAvailableDirections() const;
    Utils::Direction getBestDiretion() const;

    void wrapOutOfBounds();

    void handleEatenState();
    void handleChasingState();
    void handleIdleState();
    void handleScatterState();

    Vec2 getPinkyChasingTarget(Vec2 pacmanPosition, Utils::Direction pacmanDirection) const;
    Vec2 getInkyChasingTarget(Vec2 pacmanPosition, Utils::Direction pacmanDirection) const;
    Vec2 getClydeChasingTarget(Vec2 pacmanPosition) const;

  private:
    GhostStates m_state;
    GameController * m_gameController;
    Entities * m_entitiesRegistry;
    InputManager * m_inputManager;
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
