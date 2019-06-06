//
// Created by FLXR on 2/9/2019.
//

#include <cmath>
#include <xe/animation/spriteanimation.hpp>

namespace xe {

  SpriteAnimation::SpriteAnimation(const Texture *texture, const vec2 &imageCount, float switchTime, bool looped) :
      running(true),
      looped(looped),
      switchTime(switchTime),
      totalTime(0.0f),
      currentImage(0.0f, 0.0f),
      imageCount(imageCount) {

    textureRect.width = texture->getWidth() / imageCount.x;
    textureRect.height = texture->getHeight() / imageCount.y;
  }

  void SpriteAnimation::fixedUpdate(float delta, uint row, bool faceRight) {
    if (!running) return;

    currentImage.y = row;
    totalTime += delta;

    if (totalTime >= switchTime) {
      totalTime -= switchTime;
      ++currentImage.x;

      if (currentImage.x >= imageCount.x) {
        currentImage.x = !looped ? imageCount.x - 1 : 0.0f;
      }
    }

    textureRect.y = currentImage.y * textureRect.height;

    if (faceRight) {
      textureRect.x = currentImage.x * textureRect.width;
      textureRect.width = fabsf(textureRect.width);
    } else {
      textureRect.x = (currentImage.x + 1.0f) * fabsf(textureRect.width);
      textureRect.width = -fabsf(textureRect.width);
    }
  }

  void SpriteAnimation::reset() {
    totalTime = 0.0f;
    currentImage = vec2(0.0f);
    running = true;
  }

}
