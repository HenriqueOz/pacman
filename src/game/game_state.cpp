#include "game_state.hpp"

void
GameState::update()
{
    update_frightened_state();
}

void
GameState::update_frightened_state()
{
    if (_frightenedTimer > 0) {
        _frightenedTimer--;
    }
}