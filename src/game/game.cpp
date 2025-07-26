#include "game/game.h"
#include "config/config.h"
#include "game/entities/entities.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <game/input/input_manager.h>
#include <iostream>

Game::Game(InputManager *inputManager, Entities *entities, GameController *gameController)
  : m_isRunning(false)
  , m_inputManager(inputManager)
  , m_entities(entities)
  , m_gameController(gameController)
{
}

void
Game::run()
{
    this->init();

    Uint64 frameStart;
    Uint64 frameDuration;
    while (this->isRunning()) {
        frameStart = SDL_GetTicks();
        this->handleInput();
        this->update();
        this->render();
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
Game::handleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        m_inputManager->processInput(event);
        if (event.type == SDL_EVENT_QUIT) {
            m_isRunning = false;
        }
    }
}

void
Game::render()
{
    auto entitiesVector = m_entities->getEntitiesSortedByDepth();

    SDL_RenderClear(m_renderer);
    for (const auto &entity : entitiesVector) {
        if (entity != nullptr) {
            entity->render(m_renderer);
        }
    }

    SDL_RenderPresent(m_renderer);
}

void
Game::update()
{
    auto &entitiesMap = m_entities->getEntities();

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
