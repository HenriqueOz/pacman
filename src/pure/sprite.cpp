#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>

#include "sprite.hpp"
#include "SDL3/SDL_rect.h"

Sprite::~Sprite()
{
    if (_texture) {
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
    }
}

void
Sprite::load(SDL_Renderer * renderer, const std::string & filepath)
{
    SDL_Texture * texture = IMG_LoadTexture(renderer, filepath.c_str());
    if (texture != nullptr) {
        _texture = texture;
        SDL_Log("SPRITE_LOADED: %s", filepath.c_str());
        return;
    }
    SDL_Log("ERROR::SPRITE::FAILED_TO_LOAD_SPRITE: %s", SDL_GetError());
}

void
Sprite::render(SDL_Renderer * renderer) const
{
    if (!_texture)
        return;

    const SDL_FRect destination = { .x = _position.x,
                                    .y = _position.y,
                                    .w = static_cast<float>(_size.x),
                                    .h = static_cast<float>(_size.y) };

    SDL_RenderTexture(renderer, _texture, nullptr, &destination);
}
