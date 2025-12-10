#ifndef SPRITE_H_
#define SPRITE_H_

#include "pure/utils.hpp"
#include <string>

#include <SDL3/SDL_render.h>

class Sprite
{
  public:
    Sprite() = default;
    ~Sprite();

    void load(SDL_Renderer * renderer, const std::string & filepath);
    void render(SDL_Renderer * renderer) const;

    void set_position(const Vec2<float> & pos) { _position = pos; }
    void set_size(const Vec2<int> & size) { _size = size; }

    const Vec2<float> & get_position() const { return _position; }
    const Vec2<int> & get_size() const { return _size; }

  private:
    Vec2<float> _position{};
    Vec2<int> _size{};
    SDL_Texture * _texture = nullptr;
};

#endif