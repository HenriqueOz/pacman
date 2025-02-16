#include "game/game.hpp"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_timer.h"
#include "config/config.hpp"
#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <X11/Xmd.h>
#include <cstdint>
#include <iostream>

using namespace config;

Game::Game(World & world, InputManager & inputManager)
  : _isRunning(false)
  , _inputManager(inputManager)
  , _world(world)
{
}

Game::~Game() {}

void
Game::run()
{
    this->init();

    if (!_isRunning) {
        return;
    }

    std::uint64_t lastTick = SDL_GetTicks();
    std::uint64_t currentTick = 0;
    float deltaTime = 0;

    while (this->is_running()) {
        currentTick = SDL_GetTicks();
        deltaTime = (currentTick - lastTick) / 1000.0f;
        lastTick = currentTick;

        this->handle_input();
        this->update(deltaTime);
        this->render();

        Uint64 frameDuration = SDL_GetTicks() - currentTick;
        if (window::FRAME_DELAY > frameDuration) {
            SDL_Delay(window::FRAME_DELAY - frameDuration);
        }
    }

    this->clean();
}

void
Game::init()
{
    _isRunning = false;

    if (!TTF_Init()) {
        std::cerr << "ERROR::SDL::FAILED_TO_INIT_TTF: " << SDL_GetError() << std::endl;
        return;
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "ERROR::SDL::FAILED_TO_INIT_VIDEO_SUBMODULE: " << SDL_GetError() << std::endl;
        return;
    }

    if (!SDL_CreateWindowAndRenderer(window::TITLE,
                                     gui::TOTAL_WIDTH,
                                     gui::TOTAL_HEIGHT,
                                     SDL_WINDOW_HIGH_PIXEL_DENSITY,
                                     &_window,
                                     &_renderer)) {
        std::cerr << "ERROR::GAME::COULD_NOT_CREATE_WINDOW: " << SDL_GetError() << std::endl;
        return;
    }

    _gameTexture = SDL_CreateTexture(_renderer,
                                     SDL_GetWindowPixelFormat(_window),
                                     SDL_TEXTUREACCESS_TARGET,
                                     window::WIDTH,
                                     window::HEIGHT);

    if (!_gameTexture) {
        std::cerr << "ERROR::GAME::COULD_NOT_CREATE_gameTexture: " << SDL_GetError() << std::endl;
        return;
    }

    _guiTexture = SDL_CreateTexture(_renderer,
                                    SDL_PIXELFORMAT_ARGB8888,
                                    SDL_TEXTUREACCESS_TARGET,
                                    gui::TOTAL_WIDTH,
                                    gui::TOTAL_HEIGHT);

    if (!_guiTexture) {
        std::cerr << "ERROR::GAME::COULD_NOT_CREATE_guiTexture: " << SDL_GetError() << std::endl;
        return;
    }

    _textEngine = TTF_CreateRendererTextEngine(_renderer);
    if (!_textEngine) {
        std::cerr << "ERROR::GAME::FAILED_TO_CREATE_RENDERER_textEngine: " << SDL_GetError()
                  << std::endl;
        return;
    }

    _isRunning = true;
}

bool
Game::is_running() const
{
    return _isRunning;
}

void
Game::handle_input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        _inputManager.process_input(event);
        if (event.type == SDL_EVENT_QUIT) {
            _isRunning = false;
        }
    }
}

void
Game::render()
{
    SDL_SetRenderTarget(_renderer, _gameTexture);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_SetTextureBlendMode(_gameTexture, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(_renderer);

    _world.render(_renderer);

    SDL_SetRenderTarget(_renderer, _guiTexture);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_SetTextureBlendMode(_guiTexture, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(_renderer);

    SDL_SetRenderTarget(_renderer, nullptr);
    SDL_RenderClear(_renderer);

    SDL_FRect gameDestRect = { 0,
                               static_cast<float>(gui::TOP_HEIGHT),
                               static_cast<float>(window::WIDTH),
                               static_cast<float>(window::HEIGHT) };

    SDL_RenderTexture(_renderer, _gameTexture, nullptr, &gameDestRect);
    SDL_RenderTexture(_renderer, _guiTexture, nullptr, nullptr);

    SDL_RenderPresent(_renderer);
}

void
Game::update(float delta_time)
{
    _world.update(delta_time, _inputManager);
}

void
Game::clean()
{
    SDL_DestroyTexture(_gameTexture);
    SDL_DestroyTexture(_guiTexture);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    TTF_DestroyRendererTextEngine(_textEngine);
    SDL_Quit();
}

void
Game::close_game()
{
    _isRunning = false;
}
