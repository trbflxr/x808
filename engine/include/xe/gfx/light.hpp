//
// Created by FLXR on 3/3/2019.
//

#ifndef X808_LIGHT_HPP
#define X808_LIGHT_HPP


#include <xe/string.hpp>
#include <xe/gfx/mesh.hpp>
#include <xe/math/itransformable.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

  enum class LightType {
    Spot,
    Point
  };

  class XE_API Light : public ITransformable, public NonCopyable {
  public:
    explicit Light(const string &name, LightType type, const Mesh *mesh);
    ~Light() override;

    virtual void update() const = 0;

    inline const string &getName() const { return name; }
    inline LightType getType() const { return type; }

    inline bool isEnabled() const { return enabled; }
    inline void setEnabled(bool enabled) { Light::enabled = enabled; }

    inline bool isShadowed() const { return shadowed; }
    inline void setShadowed(bool shadowed) { Light::shadowed = shadowed; }

    inline const int32 getShadowId() const { return shadowId; }
    inline void setShadowId(int32 id) { shadowId = id; }

    inline const vec3 &getColor() const { return color; }
    inline void setColor(const vec3 &color) { Light::color = color; }

    inline float getIntensity() const { return intensity; }
    inline void setIntensity(float intensity) {
      setDirty(true);
      Light::intensity = intensity;
    }

    inline float getFalloff() const { return falloff; }
    inline void setFalloff(float falloff) {
      setDirty(true);
      Light::falloff = falloff;
    }

    inline const Mesh *getMesh() const { return mesh; }
    inline const mat4 &getBoundsMatrix() const {
      if (isDirty()) {
        update();
      }
      return boundsMatrix;
    }

  protected:
    string name;
    LightType type;
    const Mesh *mesh;

    bool enabled;
    bool shadowed;
    int32 shadowId;

    vec3 color;
    float intensity;
    float falloff;

    mutable mat4 boundsMatrix;
  };


  class XE_API SpotLight : public Light {
  public:
    explicit SpotLight(const string &name);
    ~SpotLight() override = default;

    void update() const override;

    inline float getSpotAngle() const { return spotAngle; }
    inline void setSpotAngle(float angle) {
      setDirty(true);
      spotAngle = angle;
    }

    inline float getSpotBlur() const { return spotBlur; }
    inline void setSpotBlur(float blur) { spotBlur = blur; }

    inline const mat4 &getView() const {
      if (isDirty()) {
        update();
      }
      return view;
    }

    inline const mat4 &getProjection() const {
      if (isDirty()) {
        update();
      }
      return projection;
    }

  private:
    float spotAngle;
    float spotBlur;

    mutable mat4 projection;
    mutable mat4 view;
  };


  class XE_API  PointLight : public Light {
  public:
    explicit PointLight(const string &name);
    ~PointLight() override = default;

    void update() const override;
  };


  class XE_API DirectionalLight : public ITransformable, public NonCopyable {
  public:
    explicit DirectionalLight(const string &name, const std::vector<float> &splits);
    ~DirectionalLight() override = default;

    void update() const;

    inline const string &getName() const { return name; }

    inline bool isEnabled() const { return enabled; }
    inline void setEnabled(bool enabled) { DirectionalLight::enabled = enabled; }

    inline bool isShadowed() const { return shadowed; }
    inline void setShadowed(bool shadowed) { DirectionalLight::shadowed = shadowed; }

    inline const vec3 &getColor() const { return color; }
    inline void setColor(const vec3 &color) { DirectionalLight::color = color; }

    inline float getIntensity() const { return intensity; }
    inline void setIntensity(float intensity) { DirectionalLight::intensity = intensity; }

    inline const std::vector<mat4> &getProjection() const { return projection; }

    inline const mat4 &getView() const {
      if (isDirty()) {
        update();
      }
      return view;
    }

  private:
    string name;

    bool enabled;
    bool shadowed;

    vec3 color;
    float intensity;

    std::vector<float> splits;
    std::vector<mat4> projection;
    mutable mat4 view;
  };
}

#endif //X808_LIGHT_HPP
