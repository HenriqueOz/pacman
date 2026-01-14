#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_log.h>
#include "SDL3/SDL_rect.h"

#include "sprite.hpp"

Sprite::Sprite(Vec2<float> _position, SDL_Renderer * renderer, const std::filesystem::path & filepath)
  : position(_position)
{
    this->load_image(renderer, filepath);
}

Sprite::~Sprite()
{
    if (_texture) {
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
    }
}

void
Sprite::load_image(SDL_Renderer * renderer, const std::filesystem::path & filepath)
{
    SDL_Texture * texture = IMG_LoadTexture(renderer, filepath.string().c_str());
    if (texture != nullptr) {
        _texture = texture;
        _textureSize = get_texture_size(_texture);
        SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
        return;
    }
    SDL_Log("ERROR::SPRITE::FAILED_TO_LOAD_SPRITE: %s", SDL_GetError());
}

void
Sprite::render(SDL_Renderer * renderer) const
{
    if (!_texture)
        return;

    const SDL_FRect destination = { .x = position.x,
                                    .y = position.y,
                                    .w = static_cast<float>(_textureSize.x),
                                    .h = static_cast<float>(_textureSize.y) };

    SDL_RenderTexture(renderer, _texture, nullptr, &destination);
}
