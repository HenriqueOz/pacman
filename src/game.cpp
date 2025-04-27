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
  , m_window(nullptr)
{
}

void
Game::init(Window *const window, Map *const map)
{
    m_window = window;
    if (m_window->getWindow() == nullptr) {
        m_isRunning = false;
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window->getWindow(), NULL);
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

Window *
Game::getWindow() const
{
    return m_window;
}

Map *
Game::getMap() const
{
    return m_map;
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
Game::render(std::vector<std::unique_ptr<Entity>> &entities)
{
    SDL_RenderClear(m_renderer);
    for (const auto &entity : entities) {
        entity.get()->render(m_renderer);
    }
    SDL_RenderPresent(m_renderer);
}

void
Game::update(std::vector<std::unique_ptr<Entity>> &entities)
{
    for (const auto &entity : entities) {
        entity.get()->update();
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
