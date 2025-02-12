#ifndef _GAME_H
#define _GAME_H

#include <cstddef>
#include <string>

namespace pm {
class Game
{
  public:
    Game(std::size_t window_width, std::size_t window_height);
    ~Game();

    bool is_running();
    void run();

  private:
    std::string m_window_name;
    std::size_t m_window_width;
    std::size_t m_window_height;
    bool m_is_running;

    void read_input();
    void render();
    void update();
};
}

#endif