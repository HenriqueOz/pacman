#include "game/game.h"
#include "game/window/window.h"
#include "registry/entities/entities.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <cstddef>
#include <iostream>
#include <registry/input/input_manager.h>

Game::Game()
  : m_isRunning(false)
{
}

void
Game::run(Window &window, InputManager *inputManager, Entities *entitiesRegistry)
{
    this->init(window);

    Uint64 frameStart;
    Uint64 frameDuration;
    while (this->isRunning()) {
        frameStart = SDL_GetTicks();
        this->handleInput(inputManager);
        this->update(entitiesRegistry);
        this->render(entitiesRegistry);
        frameDuration = SDL_GetTicks() - frameStart;
        if (Config::frameDelay > frameDuration) {
            SDL_Delay(Config::frameDelay - frameDuration);
        }
    }
    this->clean();
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
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        inputManager->processInput(event);
        if (event.type == SDL_EVENT_QUIT) {
            m_isRunning = false;
        }
    }
}

void
Game::render(Entities *entities)
{
    auto &entitiesMap = entities->getEntities();

    SDL_RenderClear(m_renderer);
    for (const auto &entry : entitiesMap) {
        const auto entity = entry.second.get();
        if (entity != nullptr) {
            entity->render(m_renderer);
        }
    }
    SDL_RenderPresent(m_renderer);
}

void
Game::update(Entities *entities)
{
    auto &entitiesMap = entities->getEntities();

    for (const auto &entry : entitiesMap) {
        const auto entity = entry.second.get();

        if (entity == nullptr) {
            continue;
        }

        const Vec2 &past = entity->getPosition();
        entity->update();
        const Vec2 &current = entity->getPosition();

        entities->updateEntityPositionInMap(entity, current, past);
    }
}

void
Game::clean()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

void
Game::closeGame()
{
    m_isRunning = false;
}
