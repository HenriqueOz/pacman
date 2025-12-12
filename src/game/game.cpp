#include <cstdint>
#include <iostream>

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "config/config.hpp"
#include "game/game.hpp"

using namespace config;

Game::Game(World & world,
           InputManager & inputManager,
           Input & input,
           CollisionManager & collision)
  : _isRunning(false)
  , _inputManager(inputManager)
  , _world(world)
  , _input(input)
  , _collision(collision)
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

    _world.initialize(_renderer);

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
        if (window::kFrameDelay > frameDuration) {
            SDL_Delay(window::kFrameDelay - frameDuration);
        }
    }

    this->clean();
}

void
Game::init()
{
    _isRunning = false;

    if (!TTF_Init()) {
        std::cerr << "ERROR::SDL::FAILED_TO_INIT_TTF: " << SDL_GetError()
                  << std::endl;
        return;
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "ERROR::SDL::FAILED_TO_INIT_VIDEO_SUBMODULE: "
                  << SDL_GetError() << std::endl;
        return;
    }

    if (!SDL_CreateWindowAndRenderer(window::kTitle,
                                     window::kWidth,
                                     window::kHeight,
                                     SDL_WINDOW_HIGH_PIXEL_DENSITY,
                                     &_window,
                                     &_renderer)) {
        std::cerr << "ERROR::GAME::COULD_NOT_CREATE_WINDOW: " << SDL_GetError()
                  << std::endl;
        return;
    }

    _gameTexture = SDL_CreateTexture(_renderer,
                                     SDL_GetWindowPixelFormat(_window),
                                     SDL_TEXTUREACCESS_TARGET,
                                     view::kGameTextureWidth,
                                     view::kGameTextureHeight);

    if (!_gameTexture) {
        std::cerr << "ERROR::GAME::COULD_NOT_CREATE_gameTexture: "
                  << SDL_GetError() << std::endl;
        return;
    }

    _guiTexture = SDL_CreateTexture(_renderer,
                                    SDL_PIXELFORMAT_ARGB8888,
                                    SDL_TEXTUREACCESS_TARGET,
                                    view::kSurfaceWidth,
                                    view::kSurfaceHeight);

    if (!_guiTexture) {
        std::cerr << "ERROR::GAME::COULD_NOT_CREATE_guiTexture: "
                  << SDL_GetError() << std::endl;
        return;
    }

    _textEngine = TTF_CreateRendererTextEngine(_renderer);
    if (!_textEngine) {
        std::cerr << "ERROR::GAME::FAILED_TO_CREATE_RENDERER_textEngine: "
                  << SDL_GetError() << std::endl;
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
    // Rendering to game texture
    SDL_SetRenderTarget(_renderer, _gameTexture);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_SetTextureBlendMode(_gameTexture, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(_renderer);

    _world.render(_renderer);

    // Rendering to gui texture
    SDL_SetRenderTarget(_renderer, _guiTexture);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_SetTextureBlendMode(_guiTexture, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(_renderer);

    _world.renderGui(_renderer);

    // Clearing renderer
    SDL_SetRenderTarget(_renderer, nullptr);
    SDL_RenderClear(_renderer);

    SDL_FRect gameDestRect = { 0,
                               static_cast<float>(view::kGuiTopHeight),
                               static_cast<float>(view::kGameTextureWidth),
                               static_cast<float>(view::kGameTextureHeight) };

    // Merging textures to the renderer
    SDL_RenderTexture(_renderer, _gameTexture, nullptr, &gameDestRect);
    SDL_RenderTexture(_renderer, _guiTexture, nullptr, nullptr);

    // Presenting the final result
    SDL_SetRenderScale(_renderer,
                       static_cast<float>(window::kHorizontalScale),
                       static_cast<float>(window::kVerticalScale));

    SDL_RenderPresent(_renderer);
}

void
Game::update(float deltaTime)
{
    _world.update(deltaTime, _input, _collision);
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
