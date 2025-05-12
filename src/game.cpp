#include "game.h"
#include "SDL3/SDL.h"
#include "config.h"
#include "input_manager.h"
#include "map.h"
#include <cstddef>
#include <iostream>
#include <memory>
#include <utility>

Game *Game::m_instance = nullptr;

Game::Game()
  : m_isRunning(false)
{
}

void
Game::init(Window &window)
{
    if (window.getWindow() == nullptr) {
        m_isRunning = false;
        return;
    }

    m_renderer = SDL_CreateRenderer(window.getWindow(), NULL);
    if (m_renderer == nullptr) {
        std::cout << "ERROR::GAME::COULD_NOT_CREATE_RENDERER: " << SDL_GetError() << std::endl;
        m_isRunning = false;
        return;
    }

    SDL_SetRenderLogicalPresentation(m_renderer,
                                     Config::logicalWidth,
                                     Config::logicalHeight,
                                     SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);

    m_isRunning = true;
}

bool
Game::isRunning() const
{
    return m_isRunning;
}

void
Game::handleInput(InputManager *inputManager)
{
    inputManager->processInput();
    if (inputManager->quitRequested()) {
        m_isRunning = false;
    }
}

void
Game::render(Entities &entities)
{
    auto &entitiesVec = entities.getEntities();

    SDL_RenderClear(m_renderer);
    for (const auto &entity : entitiesVec) {
        entity.get()->render(m_renderer);
    }
    SDL_RenderPresent(m_renderer);
}

void
Game::update(Entities &entities)
{
    auto &entitiesVec = entities.getEntities();
    for (const auto &entity : entitiesVec) {
        const Vec2 &past = entity.get()->getPosition();
        entity.get()->update();
        const Vec2 &current = entity.get()->getPosition();

        entities.updateEntityPositionInMap(entity.get(), current, past);
    }
}

void
Game::clean()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();

    delete m_instance;
}

void
Game::closeGame()
{
    m_isRunning = false;
}
