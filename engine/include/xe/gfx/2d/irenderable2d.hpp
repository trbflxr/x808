//
// Created by FLXR on 9/13/2018.
//

#ifndef X808_IRENDERABLE2D_HPP
#define X808_IRENDERABLE2D_HPP


#include <xe/math/vec2.hpp>
#include <xe/gfx/color.hpp>
#include <xe/gfx/texture.hpp>

namespace xe {

  struct Vertex2D {
    vec2 pos;
    vec2 uv;
  };

  class IRenderable2D {
  public:
    inline IRenderable2D(const IRenderable2D &other) :
        color(other.color),
        visible(other.visible) { }

    virtual ~IRenderable2D() = default;

    inline uint getColor() const { return color; }
    inline void setColor(uint color) { IRenderable2D::color = color; }

    inline bool isVisible() const { return visible; }
    inline void setVisible(bool visible) { IRenderable2D::visible = visible; }

    virtual const Texture *getTexture() const = 0;

    virtual uint getPointCount() const = 0;
    virtual const Vertex2D *getVertices() const = 0;

    virtual uint getIndicesCount() const = 0;
    virtual const uint *getIndices() const = 0;

    virtual const mat4 &getTransformation() const = 0;

  protected:
    explicit IRenderable2D() :
        color(color::White),
        visible(true) { }

  protected:
    uint color;
    bool visible;
  };

}

#endif //X808_IRENDERABLE2D_HPP
