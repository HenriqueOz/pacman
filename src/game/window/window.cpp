#include "window.h"
#include <iostream>

Window::Window(const char *windowName, int windowWidth, int windowHeight)
  : m_windowName(windowName)
  , m_windowWidth(windowWidth)
  , m_windowHeight(windowHeight)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "ERROR::SDL::FAILED_TO_INIT_VIDEO_SUBMODULE: " << SDL_GetError() << std::endl;
        return;
    }

    m_window = SDL_CreateWindow(
      m_windowName.c_str(), m_windowWidth, m_windowHeight, SDL_WINDOW_HIGH_PIXEL_DENSITY);
    if (m_window == nullptr) {
        std::cout << "ERROR::GAME::COULD_NOT_CREATE_WINDOW: " << SDL_GetError() << std::endl;
    }
}

Window::~Window()
{
    SDL_DestroyWindow(m_window);
}

SDL_Window *
Window::getWindow() const
{
    return m_window;
}

std::size_t
Window::getWidth() const
{
    return m_windowWidth;
}

std::size_t
Window::getHeight() const
{
    return m_windowHeight;
}

std::string
Window::getName() const
{
    return m_windowName;
}