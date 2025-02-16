#ifndef GAME_H
#define GAME_H

#include "input_manager.hpp"
#include "world.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>

class Game
{
  public:
    Game(World & world, InputManager & inputManager);
    ~Game();

    bool is_running() const;
    void run();
    void close_game();

  private:
    void init();
    void render();
    void update(float delta_time);
    void clean();
    void handle_input();

    SDL_Window * _window = nullptr;
    SDL_Renderer * _renderer = nullptr;

    SDL_Texture * _gameTexture = nullptr;
    SDL_Texture * _guiTexture = nullptr;

    TTF_TextEngine * _textEngine = nullptr;

    bool _isRunning;

    InputManager & _inputManager;
    World & _world;
};

#endif
