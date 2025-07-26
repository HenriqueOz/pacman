#include "game/game.h"
#include "config/config.h"
#include "registry/entities/entities.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <registry/input/input_manager.h>

Game::Game()
  : m_isRunning(false)
{
}

void
Game::run(InputManager *inputManager, Entities *entitiesRegistry)
{
    this->init();

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
Game::init()
{
    TTF_Init();

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "ERROR::SDL::FAILED_TO_INIT_VIDEO_SUBMODULE: " << SDL_GetError() << std::endl;
        return;
    }

    if (!SDL_CreateWindowAndRenderer(Config::windowName,
                                     Config::windowWidth,
                                     Config::windowHeight,
                                     SDL_WINDOW_HIGH_PIXEL_DENSITY,
                                     &m_window,
                                     &m_renderer)) {
        std::cout << "ERROR::GAME::COULD_NOT_CREATE_WINDOW: " << SDL_GetError() << std::endl;
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
    auto entitiesVector = entities->getEntitiesSortedByDepth();

    SDL_RenderClear(m_renderer);
    for (const auto &entity : entitiesVector) {
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

        if (entity) {
            entity->update();
        }
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
