#ifndef REGISTRY_H_
#define REGISTRY_H_

#include "registry/entities/entities.h"
#include "registry/input/input_manager.h"
#include <memory>

class Registry
{
  public:
    static InputManager *registryInputManager(std::unique_ptr<InputManager> inputManagerj);
    static InputManager *getInputManager();

    static Entities *registryEntitiesRegistry(std::unique_ptr<Entities> entitiesRegsitry);
    static Entities *getEntitiesRegistry();

  private:
    Registry() = delete;

    static std::unique_ptr<InputManager> m_inputManager;
    static std::unique_ptr<Entities> m_entitiesRegistry;
};

#endif