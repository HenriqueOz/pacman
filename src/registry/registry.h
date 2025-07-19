#ifndef REGISTRY_H_
#define REGISTRY_H_

#include "registry/controller/game_controller.h"
#include "registry/entities/entities.h"
#include "registry/input/input_manager.h"
#include <memory>

class Registry
{
  public:
    static InputManager *registryInputManager(std::unique_ptr<InputManager> inputManagerj);
    static Entities *registryEntitiesRegistry(std::unique_ptr<Entities> entitiesRegsitry);
    static GameController *registryGameController(std::unique_ptr<GameController> gameController);

    static InputManager *getInputManager();
    static Entities *getEntitiesRegistry();
    static GameController *getGameController();

  private:
    Registry() = delete;

    static std::unique_ptr<InputManager> m_inputManager;
    static std::unique_ptr<Entities> m_entitiesRegistry;
    static std::unique_ptr<GameController> m_gameController;
};

#endif