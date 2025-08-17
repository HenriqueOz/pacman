#include "gui_manager.h"
#include "config/config.h"
#include "game/controller/game_controller.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cmath>

GuiManager::GuiManager(GameController *gameController)
  : m_gameController(gameController)
{
    m_titleFont = TTF_OpenFont("assets/arcadeclassic.ttf", 28);
    m_normalFont = TTF_OpenFont("assets/arcadeclassic.ttf", 28);
}

GuiManager::~GuiManager()
{
    TTF_CloseFont(m_titleFont);
    TTF_CloseFont(m_normalFont);
}

void
GuiManager::update()
{
}

void
GuiManager::render(SDL_Renderer *renderer, TTF_TextEngine *textEngine) const
{
}

void
GuiManager::renderGUI(SDL_Renderer *renderer, TTF_TextEngine *textEngine) const
{
    drawScore(renderer, textEngine);
    drawLifesUp(renderer, textEngine);
}

void
GuiManager::drawScore(SDL_Renderer *renderer, TTF_TextEngine *textEngine) const
{
    std::string label = "SCORE";
    std::string score = std::to_string(m_gameController->getScore());

    TTF_Text *labelText = TTF_CreateText(textEngine, m_titleFont, label.c_str(), label.size());
    TTF_Text *scoreText = TTF_CreateText(textEngine, m_titleFont, score.c_str(), score.size());

    const unsigned int leftPadding = 30;
    const unsigned int topPadding = 12;

    Vec2 labelPosition = { leftPadding, topPadding };

    Vec2 scorePosition = { leftPadding, Config::topGuiHeight / 2 };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    TTF_DrawRendererText(labelText, labelPosition.x, labelPosition.y);
    TTF_DrawRendererText(scoreText, scorePosition.x, scorePosition.y);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    TTF_DestroyText(scoreText);
}

void
GuiManager::drawLifesUp(SDL_Renderer *renderer, TTF_TextEngine *textEngine) const
{
    if (std::sin(SDL_GetTicks() / 300) > 0) {
        return;
    }

    std::string label = "UP";
    std::string lifes = std::to_string(m_gameController->getPacmanLifes()) + "UP";

    TTF_Text *labelText = TTF_CreateText(textEngine, m_titleFont, label.c_str(), label.size());
    TTF_Text *lifesText = TTF_CreateText(textEngine, m_titleFont, lifes.c_str(), lifes.size());

    const unsigned int topPadding = 12;
    const unsigned int xoffset = Config::windowWidth;
    const unsigned int rightPadding = 90;

    Vec2 labelPosition = { static_cast<int>(xoffset - label.size() - rightPadding), topPadding };
    Vec2 scorePosition = { static_cast<int>(xoffset - label.size() - rightPadding),
                           Config::topGuiHeight / 2 };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    TTF_DrawRendererText(labelText, labelPosition.x, labelPosition.y);
    TTF_DrawRendererText(lifesText, scorePosition.x, scorePosition.y);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    TTF_DestroyText(lifesText);
}
