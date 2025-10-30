#ifndef _GAME_HPP
#define _GAME_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <game/controller/game_controller.hpp>
#include <game/entities/entities.hpp>
#include <game/input/input_manager.hpp>

class Game
{
  public:
    Game(InputManager * inputManager, Entities * entities, GameController * gameController);
    ~Game() {};

    bool isRunning() const;
    void init();
    void render();
    void update();
    void clean();
    void closeGame();
    void run();

  private:
    void handleInput();

    SDL_Window * m_window = nullptr;
    SDL_Renderer * m_renderer = nullptr;

    SDL_Texture * m_gameTexture = nullptr;
    SDL_Texture * m_guiTexture = nullptr;

    TTF_TextEngine * m_textEngine = nullptr;

    bool m_isRunning;

    InputManager * m_inputManager = nullptr;
    Entities * m_entities = nullptr;
    GameController * m_gameController = nullptr;
};

#endif
