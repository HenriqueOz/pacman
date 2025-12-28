#ifndef SPRITE_H_
#define SPRITE_H_

#include <string>
#include <filesystem>

#include <SDL3/SDL_render.h>

#include "game/utils.hpp"

class Sprite
{
  public:
    Vec2<float> position{};
    Vec2<int> size{};

    Sprite(Vec2<float> _position, Vec2<int> _size, SDL_Renderer * renderer, const std::filesystem::path & filepath);
    ~Sprite();

    void render(SDL_Renderer * renderer) const;
    const Vec2<int> & get_image_size() const { return _textureSize; }

  private:
    Vec2<int> _textureSize{};
    SDL_Texture * _texture = nullptr;

    void load_image(SDL_Renderer * renderer, const std::filesystem::path & filepath);
};

#endif
