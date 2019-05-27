//
// Created by FLXR on 9/26/2018.
//


#include <freetype-gl/freetype-gl.h>
#include <embedded/embedded.hpp>
#include <xe/utils/assert.hpp>
#include <xe/loaders/fontloader.hpp>
#include <xe/resources/font.hpp>

namespace xe {

  static ftgl::rendermode_t renderModeToFTGL(Font::RenderMode mode) {
    switch (mode) {
      case Font::RenderMode::Normal: return ftgl::RENDER_NORMAL;
      case Font::RenderMode::OutlineEdge: return ftgl::RENDER_OUTLINE_EDGE;
      case Font::RenderMode::SignedDistanceField: return ftgl::RENDER_SIGNED_DISTANCE_FIELD;
      default: return ftgl::RENDER_NORMAL;
    }
  }

  Font::Font(const string &name, const string &path, float size) :
      name(name),
      path(path),
      size(size * 1.3f),
      texture(nullptr),
      deleteFontData(true),
      fontData(nullptr) {

    const uint atlasSize = computeAtlasSize(size);

    if (!FontLoader::load(this, path, Font::size, atlasSize)) {
      XE_CORE_INFO("[Font]: default font set instead of '", path, "'");
      FontLoader::load(this, internal::DEFAULT_FONT_DATA, internal::DEFAULT_FONT_DATA_SIZE, size, atlasSize);
    }

    createAtlas(atlasSize);
  }

  Font::Font(const string &name, const byte *data, uint dataSize, float size, bool deleteData) :
      name(name),
      path("NULL"),
      size(size * 1.3f),
      texture(nullptr),
      deleteFontData(deleteData),
      fontData(nullptr) {

    const uint atlasSize = computeAtlasSize(size);

    FontLoader::load(this, data, dataSize, Font::size, atlasSize);

    createAtlas(atlasSize);
  }

  Font::~Font() {
    texture_atlas_delete(static_cast<ftgl::texture_atlas_t *>(atlas));
    texture_font_delete(static_cast<ftgl::texture_font_t *>(font));

    delete texture;

    if (deleteFontData) delete[] fontData;
  }

  void Font::createAtlas(uint size) {
    //create texture
    static TextureParameters params(TextureTarget::Tex2D,
                                    PixelInternalFormat::Alpha,
                                    PixelFormat::Alpha,
                                    PixelType::UnsignedByte);

    texture = new Texture(name + "_FontTexture", size, size, 0, params);
    texture->setData2D(static_cast<ftgl::texture_atlas_t *>(atlas)->data);
  }

  const Texture *Font::getTexture() const {
    updateAtlas();
    return texture;
  }

  void Font::updateAtlas() const {
    ftgl::texture_atlas_t *a = static_cast<ftgl::texture_atlas_t *>(atlas);

    if (a->dirty) {
      texture->setData2D(a->data);
      a->dirty = false;
    }
  }

  void *Font::getGlyph(const char *code) const {
    return ftgl::texture_font_get_glyph(static_cast<ftgl::texture_font_t *>(font), code);
  }

  float Font::getKerning(void *glyph, const char *c) const {
    return ftgl::texture_glyph_get_kerning(static_cast<ftgl::texture_glyph_t *>(glyph), c);
  }

  void Font::setOutlineThickness(float thickness) const {
    static_cast<ftgl::texture_font_t *>(font)->outline_thickness = thickness;
  }

  void Font::setRenderMode(RenderMode mode) const {
    static_cast<ftgl::texture_font_t *>(font)->rendermode = renderModeToFTGL(mode);
  }

  uint Font::computeAtlasSize(float fontSize) {
    if (fontSize <= 50) return 1024;
    if (fontSize <= 100) return 2048;
    if (fontSize <= 150) return 4096;
    if (fontSize <= 200) return 8192;
    return 8192;
  }

}