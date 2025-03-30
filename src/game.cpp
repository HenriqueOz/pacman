#include "game.h"
#include "SDL3/SDL.h"
#include <cstddef>
#include <iostream>
#include <memory>
#include <utility>

const Uint32 WINDOW_WIDTH = 400;
const Uint32 WINDOW_HEIGHT = 400;

pm::Game *pm::Game::m_instance = nullptr;

pm::Game::Game()
  : m_isRunning(false)
  , m_windowWidth(WINDOW_WIDTH)
  , m_windowHeight(WINDOW_HEIGHT)
  , m_windowName("pacman")
{
}

void
pm::Game::init()
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
pm::Game::isRunning() const
{
    return m_isRunning;
}

void
pm::Game::render()
{
    SDL_RenderClear(m_renderer);

    SDL_RenderPresent(m_renderer);
}

void
pm::Game::update()
{
}

void
pm::Game::clean()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();

    delete m_instance;
}