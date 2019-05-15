//
// Created by FLXR on 8/18/2018.
//

#ifndef X808_TEXT_HPP
#define X808_TEXT_HPP


#include <xe/gfx/color.hpp>
#include <xe/resources/fontmanager.hpp>
#include <xe/math/itransformable2d.hpp>

namespace xe {

  class Text : public ITransformable2D {
  public:
    explicit Text(const string &string, const Font *font = GETFONT("default"), float scale = 1.0f) noexcept :
        font(font),
        string(string),
        textColor(color::White),
        outlineColor(color::Transparent),
        outlineThickness(0.0f),
        scale(scale) { }

    inline Text(const Text &other) :
        ITransformable2D(other),
        font(other.font),
        string(other.string),
        textColor(other.textColor),
        outlineColor(other.outlineColor),
        outlineThickness(other.outlineThickness),
        scale(other.scale) { }

    inline const Font *getFont() const { return font; }
    inline void setFont(const Font *font) { Text::font = font; }

    inline string &getString() { return string; }
    inline const string &getString() const { return string; }
    inline void setString(const string &string) { Text::string = string; }

    inline uint getTextColor() const { return textColor; }
    inline void setTextColor(uint textColor) { Text::textColor = textColor; }

    inline uint getOutlineColor() const { return outlineColor; }
    inline void setOutlineColor(uint outlineColor) { Text::outlineColor = outlineColor; }

    inline float getFontScale() const { return scale; }
    inline void setFontScale(float scale) { Text::scale = scale; }

    inline float getOutlineThickness() const { return outlineThickness; }
    inline void setOutlineThickness(float thickness) { Text::outlineThickness = thickness; }

  private:
    const Font *font;
    string string;
    uint textColor;
    uint outlineColor;
    float outlineThickness;
    float scale;
  };

}


#endif //X808_TEXT_HPP
