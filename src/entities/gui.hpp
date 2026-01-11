#ifndef GUI_H_
#define GUI_H_

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "game/game_state.hpp"

class Gui
{
  public:
    Gui(SDL_Renderer * renderer);
    ~Gui();

    void render(SDL_Renderer * renderer, const GameState & state);

  private:
    TTF_Font * _font = nullptr;

    void render_game_over(SDL_Renderer * renderer);
    void render_win(SDL_Renderer * renderer);
    void render_text_centered(SDL_Renderer * renderer, const char * text, float offsetY);
};

#endif
