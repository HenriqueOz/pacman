#include "game.h"

pm::Game::Game(std::size_t window_width, std::size_t window_height)
  : m_is_running(false)
  , m_window_width(window_width)
  , m_window_height(window_height)
  , m_window_name("paman")
{
}

bool
pm::Game::is_running()
{
    return m_is_running;
}

void
pm::Game::run()
{
}

void
pm::Game::read_input()
{
}

void
pm::Game::render()
{
}

void
pm::Game::update()
{
}