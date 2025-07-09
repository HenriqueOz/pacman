#include "registry.h"
#include <utility>

std::unique_ptr<InputManager> Registry::m_inputManager = nullptr;
std::unique_ptr<Entities> Registry::m_entitiesRegistry = nullptr;

InputManager *
Registry::registryInputManager(std::unique_ptr<InputManager> inputManager)
{
    m_inputManager = std::move(inputManager);
    return m_inputManager.get();
}

InputManager *
Registry::getInputManager()
{
    return m_inputManager.get();
}

Entities *
Registry::registryEntitiesRegistry(std::unique_ptr<Entities> entitiesRegsitry)
{
    m_entitiesRegistry = std::move(entitiesRegsitry);
    return m_entitiesRegistry.get();
}

Entities *
Registry::getEntitiesRegistry()
{
    return m_entitiesRegistry.get();
}
