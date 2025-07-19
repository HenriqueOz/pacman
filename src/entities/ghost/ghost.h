#ifndef _GHOST_H
#define _GHOST_H

#include <entities/entity.h>

enum class GhostStates
{
    Idle,
    Escaping,
    Chasing,
    Dead,
};

class Ghost : public Entity
{
  public:
    Ghost(Vec2 const &pos);
    ~Ghost() override {};
    EntityType getType() const override { return GHOST; };

    void update() override;
    void render(SDL_Renderer *renderer) const override;

  private:
    GhostStates m_state;
};

#endif