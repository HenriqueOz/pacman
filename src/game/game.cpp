#include "game/game.h"
#include "config/config.h"
#include "game/entities/entities.h"
#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <game/input/input_manager.h>
#include <iostream>

Game::Game(InputManager *inputManager, Entities *entities, GameController *gameController)
  : m_isRunning(false)
  , m_inputManager(inputManager)
  , m_entities(entities)
  , m_gameController(gameController)
{

}

void
Game::run()
{
    this->init();

    Uint64 frameStart;
    Uint64 frameDuration;
    while (this->isRunning()) {
        frameStart = SDL_GetTicks();
        this->handleInput();
        this->update();
        this->render();
        frameDuration = SDL_GetTicks() - frameStart;
        if (Config::frameDelay > frameDuration) {
            SDL_Delay(Config::frameDelay - frameDuration);
        }
    }
    this->clean();
}

void
Game::init()
{
    m_isRunning = false;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "ERROR::SDL::FAILED_TO_INIT_VIDEO_SUBMODULE: " << SDL_GetError() << std::endl;
        return;
    }

    if (!SDL_CreateWindowAndRenderer(Config::windowName,
                                     Config::windowWidth,
                                     Config::windowHeight,
                                     SDL_WINDOW_HIGH_PIXEL_DENSITY,
                                     &m_window,
                                     &m_renderer)) {
        std::cerr << "ERROR::GAME::COULD_NOT_CREATE_WINDOW: " << SDL_GetError() << std::endl;
        return;
    }

    m_gameTexture = SDL_CreateTexture(m_renderer,
                                      SDL_GetWindowPixelFormat(m_window),
                                      SDL_TEXTUREACCESS_TARGET,
                                      Config::logicalWidth,
                                      Config::logicalHeight);

    if (!m_gameTexture) {
        std::cerr << "ERROR::GAME::COULD_NOT_CREATE_GAME_TEXTURE: " << SDL_GetError() << std::endl;
        return;
    }

    m_guiTexture = SDL_CreateTexture(m_renderer,
                                     SDL_PIXELFORMAT_ARGB8888,
                                     SDL_TEXTUREACCESS_TARGET,
                                     Config::windowWidth,
                                     Config::windowHeight);

    if (!m_guiTexture) {
        std::cerr << "ERROR::GAME::COULD_NOT_CREATE_GUI_TEXTURE: " << SDL_GetError() << std::endl;
        return;
    }

    m_textEngine = TTF_CreateRendererTextEngine(m_renderer);
    if (!m_textEngine) {
        std::cerr << "ERROR::GAME::FAILED_TO_CREATE_RENDERER_TEXT_ENGINE: " << SDL_GetError()
                  << std::endl;
        return;
    }

    m_isRunning = true;
}

bool
Game::isRunning() const
{
    return m_isRunning;
}

void
Game::handleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        m_inputManager->processInput(event);
        if (event.type == SDL_EVENT_QUIT) {
            m_isRunning = false;
        }
    }
}

void
Game::render()
{
    auto entitiesVector = m_entities->getEntitiesSortedByDepth();

    SDL_SetRenderTarget(m_renderer, m_gameTexture);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_SetTextureBlendMode(m_gameTexture, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(m_renderer);

    for (const auto &entity : entitiesVector) {
        if (entity != nullptr) {
            entity->render(m_renderer, m_textEngine);
        }
    }

    SDL_SetRenderTarget(m_renderer, m_guiTexture);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
    SDL_SetTextureBlendMode(m_guiTexture, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(m_renderer);

    for (const auto &entity : entitiesVector) {
        if (entity != nullptr) {
            entity->renderGUI(m_renderer, m_textEngine);
        }
    }

    SDL_SetRenderTarget(m_renderer, nullptr);
    SDL_RenderClear(m_renderer);

    SDL_FRect gameDestRect = { Config::gameRenderXOffset,
                               Config::gameRenderYOffset,
                               Config::logicalWidth,
                               Config::logicalHeight };

    SDL_RenderTexture(m_renderer, m_gameTexture, nullptr, &gameDestRect);
    SDL_RenderTexture(m_renderer, m_guiTexture, nullptr, nullptr);

    SDL_RenderPresent(m_renderer);
}

void
Game::update()
{
    auto &entitiesMap = m_entities->getEntities();

    for (const auto &entry : entitiesMap) {
        const auto entity = entry.second.get();

        if (entity) {
            entity->update();
        }
    }
}

void
Game::clean()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

void
Game::closeGame()
{
    m_isRunning = false;
}
