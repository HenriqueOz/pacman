#ifndef _GHOST_H
#define _GHOST_H

#include "registry/controller/game_controller.h"
#include <array>
#include <entities/entity.h>

enum class GhostStates
{
    IDLE,
    ESCAPING,
    CHASING,
    DEAD,
};

class Ghost : public Entity
{
  public:
    Ghost(Vec2 const &pos);
    ~Ghost() override {};
    EntityType getType() const override { return GHOST; };

    void update() override;
    void render(SDL_Renderer *renderer) const override;
    void moveTo(Vec2 position);
    void drawTriangleToTarget(SDL_Renderer *renderer, Vec2 target) const;
    void exitSpawn();

  private:
    GhostStates m_state;
    GameController *m_gameController;

    std::array<int, 4> axis = { 0 };
};

#endif