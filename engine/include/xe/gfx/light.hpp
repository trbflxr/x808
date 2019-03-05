//
// Created by FLXR on 3/3/2019.
//

#ifndef X808_LIGHT_HPP
#define X808_LIGHT_HPP


#include <xe/string.hpp>
#include <xe/gfx/mesh.hpp>
#include <xe/math/itransformable.hpp>

namespace xe {

	enum class LightType {
		Spot,
		Point,
		Directional
	};

	class XE_API Light : public ITransformable {
	public:
		explicit Light(const string &name, LightType type, const Mesh *mesh);

		virtual void update() = 0;

		inline const string &getName() const { return name; }
		inline LightType getType() const { return type; }

		inline bool isEnabled() const { return enabled; }
		inline void setEnabled(bool enabled) { Light::enabled = enabled; }

		inline bool isShadowed() const { return shadowed; }
		inline void setShadowed(bool shadowed) { Light::shadowed = shadowed; }

		inline const vec3 &getColor() const { return color; }
		inline void setColor(const vec3 &color) { Light::color = color; }

		inline float getIntensity() const { return intensity; }
		inline void setIntensity(float intensity) { Light::intensity = intensity; }

		inline float getFalloff() const { return falloff; }
		inline void setFalloff(float falloff) { Light::falloff = falloff; }

		inline const Mesh *getMesh() const { return mesh; }
		inline const mat4 &getBoundsMatrix() const { return boundsMatrix; }

	protected:
		string name;
		LightType type;
		const Mesh *mesh;

		bool enabled;
		bool shadowed;

		vec3 color;
		float intensity;
		float falloff;

		mat4 boundsMatrix;
	};


	class XE_API SpotLight : public Light {
	public:
		explicit SpotLight(const string &name, const Mesh *mesh);

		void update() override;

		inline float getSpotAngle() const { return spotAngle; }
		inline void setSpotAngle(float angle) { spotAngle = angle; }

		inline float getSpotBlur() const { return spotBlur; }
		inline void setSpotBlur(float blur) { spotBlur = blur; }

	private:
		float spotAngle;
		float spotBlur;
	};


	class XE_API  PointLight : public Light {
	public:
		explicit PointLight(const string &name, const Mesh *mesh);

		void update() override;
	};


	class XE_API DirectionalLight : public Light {
	public:
		explicit DirectionalLight(const string &name, bool shadow = true);

		void update() override;
	};
}

#endif //X808_LIGHT_HPP