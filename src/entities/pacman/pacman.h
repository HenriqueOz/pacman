#ifndef _PACMAN_H
#define _PACMAN_H

#include "registry/entities/entities.h"
#include "registry/input/input_manager.h"
#include <entities/entity.h>

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum PacmanState
{
    IDLE,
    MOVING,
    DEAD
};

class Pacman : public Entity
{

  public:
    Pacman(Vec2 const &pos);
    ~Pacman() override {};

    void update() override;
    void render(SDL_Renderer *renderer) const override;
    EntityType getType() const override { return PACMAN; };

    void handleInput();
    void idle();
    void moving();
    void horizontalMovement(int pastDirX, int pastDirY);
    void verticalMovement(int pastDirX, int pastDirY);

    void wrapOutOfBounds();

  private:
    InputManager *m_inputManager;
    Entities *m_entitiesRegistry;
    Vec2 m_velocity;

    PacmanState m_PacmanState;

    int m_speed;
    int m_dirx;
    int m_diry;

    const SDL_Keycode m_left = SDLK_LEFT;
    const SDL_Keycode m_right = SDLK_RIGHT;
    const SDL_Keycode m_up = SDLK_UP;
    const SDL_Keycode m_down = SDLK_DOWN;
};

#endif