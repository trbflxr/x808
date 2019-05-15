//
// Created by FLXR on 6/28/2018.
//

#include <xe/math/rect.hpp>
#include <xe/math/aabb.hpp>

namespace xe {

  rect::rect() : position(0.0f, 0.0f), size(0.0f, 0.0f) { }
  rect::rect(const rect &other) : position(other.position), size(other.size) { }
  rect::rect(const aabb &aabb) : position(vec2(aabb.min)), size(vec2(aabb.getSize())) { }
  rect::rect(const vec2 &position, const vec2 &size) : position(position), size(size) { }
  rect::rect(float x, float y, float width, float height) : position(x, y), size(width, height) { }

  bool rect::intersects(const rect &other) const {
    return position < other.position + other.size && position + size > other.position;
  }

  bool rect::contains(const vec2 &point) const {
    return point > getMinBound() && point < getMaxBound();
  }

  bool rect::contains(const vec3 &point) const {
    return contains(vec2(point));
  }

  bool rect::contains(const rect &other) const {
    return x >= other.x && y >= other.y &&
           x + width <= other.x + other.width &&
           y + height <= other.y + other.height;
  }

}