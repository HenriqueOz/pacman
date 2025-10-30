#define _GUI_MANAGER_HPP

#include "entities/entity.hpp"
#include "game/controller/game_controller.hpp"

class GuiManager : public Entity
{
  public:
    GuiManager(GameController * gameController);
    ~GuiManager() override;

    void update() override;
    void render(SDL_Renderer * renderer, TTF_TextEngine * textEngine) const override;
    void renderGUI(SDL_Renderer * renderer, TTF_TextEngine * textEngine) const override;
    EntityType getType() const override { return EntityType::GUI; };

    void drawScore(SDL_Renderer * renderer, TTF_TextEngine * textEngine) const;
    void drawLifesUp(SDL_Renderer * renderer, TTF_TextEngine * textEngine) const;
    void drawLifes(SDL_Renderer * renderer, TTF_TextEngine * textEngine) const;
    void drawFruits(SDL_Renderer * renderer, TTF_TextEngine * textEngine) const;

  private:
    TTF_Font * m_titleFont = nullptr;
    TTF_Font * m_normalFont = nullptr;

    GameController * m_gameController = nullptr;
};
