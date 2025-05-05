#ifndef _GHOST_H
#define _GHOST_H

#include "entities.h"
#include "entity.h"
#include "input_manager.h"

class Ghost : public Entity
{
  public:
    Ghost(InputManager *const inputManager, Entities *entitiesRegistry);
    ~Ghost() override{};
    EntityType getType() const override { return GHOST; };

    void update() override;
    void render(SDL_Renderer *renderer) const override;

  private:
    InputManager *m_inputManager = nullptr;
    Entities *m_entitiesRegistry = nullptr;
};

#endif