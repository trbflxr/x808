//
// Created by FLXR on 3/2/2019.
//

#ifndef X808_MATERIAL_HPP
#define X808_MATERIAL_HPP


#include <xe/gfx/texture.hpp>
#include <xe/math/vec3.hpp>

namespace xe {

  class Material {
  public:
    explicit Material(const string &name) :
        name(name),
        diffuseColor(1.0f),
        emission(1.0f),
        specularColor(1.0f),
        specularShininess(0.0f),
        heightScale(0.01f),
        useDiffuse(true),
        useSpecular(true),
        useNormal(true),
        useHeight(true),
        diffuse(nullptr),
        specular(nullptr),
        normal(nullptr),
        height(nullptr) { }


    inline const string &getName() const { return name; }

    inline const vec3 &getDiffuseColor() const { return diffuseColor; }
    inline void setDiffuseColor(const vec3 &color) { diffuseColor = color; }

    inline float getEmission() const { return emission; }
    inline void setEmission(float emission) { Material::emission = emission; }

    inline const vec3 &getSpecularColor() const { return specularColor; }
    inline void setSpecularColor(const vec3 &color) { specularColor = color; }

    inline float getSpecularShininess() const { return specularShininess; }
    inline void setSpecularShininess(float shininess) { specularShininess = shininess; }

    inline float getHeightScale() const { return heightScale; }
    inline void setHeightScale(float scale) { heightScale = scale; }

    inline const Texture *getDiffuse() const { return diffuse; }
    inline void setDiffuse(const Texture *texture) { diffuse = texture; }

    inline const Texture *getSpecularMap() const { return specular; }
    inline void setSpecularMap(const Texture *texture) { specular = texture; }

    inline const Texture *getNormalMap() const { return normal; }
    inline void setNormalMap(const Texture *texture) { normal = texture; }

    inline const Texture *getHeightMap() const { return height; }
    inline void setHeightMap(const Texture *texture) { height = texture; }

    inline bool isUseDiffuse() const { return useDiffuse; }
    inline void setUseDiffuse(bool use) { useDiffuse = use; }

    inline bool isUseSpecular() const { return useSpecular; }
    inline void setUseSpecular(bool use) { useSpecular = use; }

    inline bool isUseNormal() const { return useNormal; }
    inline void setUseNormal(bool use) { useNormal = use; }

    inline bool isUseHeight() const { return useHeight; }
    inline void setUseHeight(bool use) { useHeight = use; }

  private:
    string name;

    vec3 diffuseColor;
    float emission;

    vec3 specularColor;
    float specularShininess;

    float heightScale;

    bool useDiffuse;
    bool useSpecular;
    bool useNormal;
    bool useHeight;

    const Texture *diffuse;
    const Texture *specular;
    const Texture *normal;
    const Texture *height;
  };

}


#endif //X808_MATERIAL_HPP
