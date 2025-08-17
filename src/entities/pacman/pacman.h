#ifndef _PACMAN_H
#define _PACMAN_H

#include "entities/utils/movement.h"
#include "game/controller/game_controller.h"
#include "game/entities/entities.h"
#include "game/input/input_manager.h"
#include <SDL3/SDL_keycode.h>
#include <entities/entity.h>

enum PacmanState
{
    IDLE,
    MOVING,
    DEAD
};

class Pacman : public Entity
{

  public:
    Pacman(Vec2 const &pos,
           InputManager *inputManager,
           Entities *entitiesRegistry,
           GameController *gameController);

    ~Pacman() override {};

    void update() override;
    void render(SDL_Renderer *renderer, TTF_TextEngine *textEngine) const override;
    void renderGUI(SDL_Renderer *renderer, TTF_TextEngine *textEngine) const override;
    EntityType getType() const override { return PACMAN; };

    void handleInput();
    void changeDirectionsByKeyPressed(SDL_Keycode keycode, Utils::Direction direction);

    void idle();
    void moving();

    void handleCollision(int pastDirX, int pastDirY);
    bool hasColliderAt(int x, int y) const;
    bool canMoveTo(Utils::Direction direction) const;
    void handleFoodEating();

    void wrapOutOfBounds();

    Utils::Direction getDirection() const;
    Utils::Direction getFacingDirection() const;

  private:
    InputManager *m_inputManager = nullptr;
    Entities *m_entitiesRegistry = nullptr;
    GameController *m_gameController = nullptr;
    Vec2 m_velocity;

    PacmanState m_PacmanState;
    Utils::Direction m_facingDirection;

    int m_speed;
    int m_dirx;
    int m_diry;

    const SDL_Keycode m_left = SDLK_LEFT;
    const SDL_Keycode m_right = SDLK_RIGHT;
    const SDL_Keycode m_up = SDLK_UP;
    const SDL_Keycode m_down = SDLK_DOWN;
};

#endif
