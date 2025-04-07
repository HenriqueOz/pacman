#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL3/SDL.h>
#include <cstddef>
#include <string>

class Window
{
  private:
    std::string m_windowName;
    std::size_t m_windowWidth;
    std::size_t m_windowHeight;

    SDL_Window *m_window;

  public:
    Window(const char *windowName, int windowWidth, int windowHeight);
    ~Window();

    SDL_Window *getWindow() const;

    std::size_t getWidth() const;
    std::size_t getHeight() const;
    std::string getName() const;
};

#endif