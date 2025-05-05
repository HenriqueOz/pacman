#ifndef _PACMAN_H
#define _PACMAN_H

#include "entity.h"
#include "input_manager.h"
#include "map.h"
#include "vec.h"
#include "window.h"

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
    Pacman(InputManager *const inputManager);
    ~Pacman() override{};

    void update() override;
    void render(SDL_Renderer *renderer) const override;
    EntityType getType() const override { return PACMAN; };

    void handleInput();
    void idle();
    void moving();

    void wrapOutOfBounds();

  private:
    InputManager *m_inputManager = nullptr;
    Vec2 m_position;
    Vec2 m_velocity;

    PacmanState m_PacmanState = IDLE;

    int m_speed = 2;
    int m_dirx = 0;
    int m_diry = 0;
    Map *m_map = nullptr;

    const SDL_Keycode m_left = SDLK_LEFT;
    const SDL_Keycode m_right = SDLK_RIGHT;
    const SDL_Keycode m_up = SDLK_UP;
    const SDL_Keycode m_down = SDLK_DOWN;
};

#endif