#ifndef _ENTITY_H
#define _ENTITY_H

#include "input_manager.h"

class Entity
{
  public:
    virtual ~Entity(){};
    virtual void update() = 0;
    virtual void render() const;

  protected:
    Entity(InputManager *const inputManager);

    InputManager *const m_inputManager;
};

#endif
