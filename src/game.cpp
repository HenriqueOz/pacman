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
  , m_windowWidth(WINDOW_WIDTH)
  , m_windowHeight(WINDOW_HEIGHT)
  , m_windowName("pacman")
{
}

void
Game::init()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "ERROR::SDL::FAILED_TO_INIT_VIDEO_SUBMODULE: " << SDL_GetError() << std::endl;
        return;
    }

    m_window = SDL_CreateWindow(m_windowName.c_str(), m_windowWidth, m_windowHeight, 0);
    if (m_window == nullptr) {
        std::cout << "ERROR::GAME::COULD_NOT_CREATE_WINDOW: " << SDL_GetError() << std::endl;
        m_isRunning = false;
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window, 0);
    if (m_renderer == nullptr) {
        std::cout << "ERROR::GAME::COULD_NOT_CREATE_RENDERER: " << SDL_GetError() << std::endl;
        m_isRunning = false;
        return;
    }

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
Game::render(std::vector<Entity *> entities)
{
    SDL_RenderClear(m_renderer);
    for (Entity *const entity : entities) {
        entity->render(m_renderer);
    }
    SDL_RenderPresent(m_renderer);
}

void
Game::update(std::vector<Entity *> entities)
{
    for (Entity *const entity : entities) {
        entity->update();
    }
}

void
Game::clean()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();

    delete m_instance;
}

void
Game::closeGame()
{
    m_isRunning = false;
}
