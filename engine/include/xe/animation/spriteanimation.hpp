//
// Created by FLXR on 2/9/2019.
//

#ifndef X808_SPRITEANIMATION_HPP
#define X808_SPRITEANIMATION_HPP


#include <xe/math/vec2.hpp>
#include <xe/math/rect.hpp>
#include <xe/gfx/texture.hpp>

namespace xe {

  class XE_API SpriteAnimation {
  public:
    explicit SpriteAnimation(const Texture *texture, const vec2 &imageCount, float switchTime, bool looped = true);

    void fixedUpdate(float delta, uint row, bool faceRight);

    void reset();

    inline const rect &getTextureRect() const { return textureRect; }

    inline bool isLooped() const { return looped; }
    inline void setLooped(bool looped) { SpriteAnimation::looped = looped; }

    inline bool isRunning() const { return running; }
    inline void setRunning(bool running) { SpriteAnimation::running = running; }

  private:
    bool looped;
    bool running;

    float switchTime;
    float totalTime;

    rect textureRect;

    vec2 currentImage;
    vec2 imageCount;
  };

}


#endif //X808_SPRITEANIMATION_HPP
