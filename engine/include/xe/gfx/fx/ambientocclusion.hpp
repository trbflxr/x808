//
// Created by FLXR on 3/20/2019.
//

#ifndef X808_AMBIENTOCCLUSION_HPP
#define X808_AMBIENTOCCLUSION_HPP


#include <xe/gfx/fx/ssao.hpp>
#include <xe/gfx/fx/hbao.hpp>

namespace xe { namespace fx {

  enum class AOType {
    Ssao,
    Hbao,
    None
  };

  class XE_API AmbientOcclusion : public RenderEffect, NonCopyable {
  public:
    explicit AmbientOcclusion(uint width, uint height, AOType type);
    ~AmbientOcclusion() override;

    void calculateAO(const Texture *position, const Texture *normal, const Texture *depth,
                     const Camera *camera, const Quad *quad);

    inline AOType getType() const { return type; }
    inline void setType(AOType type) { AmbientOcclusion::type = type; }

    const Texture *getAO() const;

    static const char *typeToString(AOType type);
    static AOType stringToType(const char *ao);

  private:
    AOType type;

    SSAO *ssao;
    HBAO *hbao;
  };

}}


#endif //X808_AMBIENTOCCLUSION_HPP
