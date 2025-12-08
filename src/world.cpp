#include "world.hpp"
#include "game/input.hpp"
#include "pure/pacman.hpp"

World::World()
{
    this->initialize();
}

void
World::initialize()
{
    _pacman = create_pacman(10.f, 10.f);
}

void
World::update(float deltaTime, Input & input)
{
    update_pacman(deltaTime, input, _pacman.get());
}

void
World::render(SDL_Renderer * renderer)
{
    render_pacman(renderer, _pacman.get());
}

void
World::renderGui(SDL_Renderer * renderer)
{
}
