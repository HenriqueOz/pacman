#include "game.h"
#include "SDL3/SDL.h"
#include "input_manager.h"
#include <cstddef>
#include <iostream>
#include <memory>
#include <utility>

const Uint32 WINDOW_WIDTH = 400;
const Uint32 WINDOW_HEIGHT = 400;

Game *Game::m_instance = nullptr;

Game::Game()
  : m_isRunning(false)
  , m_window(nullptr)
{
}

void
Game::init(Window *const window)
{
    m_window = window;
    if (m_window->getWindow() == nullptr) {
        m_isRunning = false;
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window->getWindow(), 0);
    if (m_renderer == nullptr) {
        std::cout << "ERROR::GAME::COULD_NOT_CREATE_RENDERER: " << SDL_GetError() << std::endl;
        m_isRunning = false;
        return;
    }

    m_isRunning = true;
}

Window *
Game::getWindow() const
{
    return m_window;
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
