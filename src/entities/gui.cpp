#include "entities/gui.hpp"
#include "config/config.hpp"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

using namespace config;

Gui::Gui(SDL_Renderer * renderer)
{
    _font = TTF_OpenFont(config::assets::kArcadeFont.string().c_str(), 16.0f);
    if (!_font) {
        std::cerr << "ERROR::GUI::FAILED_TO_LOAD_FONT: " << SDL_GetError() << std::endl;
    }
}

Gui::~Gui()
{
    if (_font) {
        TTF_CloseFont(_font);
    }
}

void
Gui::render(SDL_Renderer * renderer, const GameState & state)
{
    State currentState = state.get_state();

    if (currentState == State::kGameOver) {
        render_game_over(renderer);
    } else if (currentState == State::kWin) {
        render_win(renderer);
    }
}

void
Gui::render_game_over(SDL_Renderer * renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    render_text_centered(renderer, "GAME  OVER", -20.0f);
    render_text_centered(renderer, "PRESS  R  TO  RESTART", 20.0f);
}

void
Gui::render_win(SDL_Renderer * renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    render_text_centered(renderer, "YOU  WIN", -20.0f);
    render_text_centered(renderer, "PRESS  R  TO  RESTART", 20.0f);
}

void
Gui::render_text_centered(SDL_Renderer * renderer, const char * text, float offsetY)
{
    if (!_font) {
        return;
    }

    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Surface * textSurface = TTF_RenderText_Solid(_font, text, 0, white);

    if (!textSurface) {
        return;
    }

    SDL_Texture * textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    if (textTexture) {
        SDL_SetTextureScaleMode(textTexture, SDL_SCALEMODE_NEAREST);

        float textWidth = static_cast<float>(textSurface->w);
        float textHeight = static_cast<float>(textSurface->h);

        SDL_FRect textRect = { (view::kSurfaceWidth - textWidth) / 2.0f,
                               (view::kSurfaceHeight - textHeight) / 2.0f + offsetY,
                               textWidth,
                               textHeight };

        SDL_RenderTexture(renderer, textTexture, nullptr, &textRect);
        SDL_DestroyTexture(textTexture);
    }

    SDL_DestroySurface(textSurface);
}
