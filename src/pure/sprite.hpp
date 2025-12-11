#ifndef SPRITE_H_
#define SPRITE_H_

#include "pure/utils.hpp"
#include <string>

#include <SDL3/SDL_render.h>

class Sprite
{
  public:
    Vec2<float> position{};
    Vec2<int> size{};

    Sprite() = default;
    ~Sprite();

    void load(SDL_Renderer * renderer, const std::string & filepath);
    void render(SDL_Renderer * renderer) const;

    const Vec2<int> & get_image_size() const { return _textureSize; }

  private:
    Vec2<int> _textureSize{};
    SDL_Texture * _texture = nullptr;
};

#endif
