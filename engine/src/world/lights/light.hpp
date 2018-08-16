//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_LIGHT_HPP
#define X808_LIGHT_HPP


#include "world/worldobject.hpp"
#include "world/model/uniquemesh.hpp"

namespace xe {

	class Light : public WorldObject {
	public:
		friend class LightManager;

	public:
		enum class Type {
			Spot,
			Point,
			Directional
		};

	public:
		bool enabled;
		bool shadowed;

		vec3 color;
		float intensity;
		float objectEmission;
		float falloff;

	public:
		explicit Light(const std::string_view &id, Light::Type type, const vec3 &color,
		               float intensity, float falloff, bool shadow, const mat4 &transformation) :
				WorldObject(SpatialData(transformation)),
				id(shadowId - 1),
				enabled(false),
				type(type),
				color(color),
				intensity(intensity),
				falloff(falloff),
				shadowed(shadowed),
				boundsMatrix(mat4(1.0f)),
				objectEmission(intensity) { }

		virtual ~Light() {
			delete mesh;
			delete boundingMesh;
		}


		int32 getLightId() const { return id; }
		int32 getShadowId() const { return shadowId; }
		Type getType() const { return type; }

		UniqueMesh *getMesh() const { return mesh; }
		UniqueMesh *getBoundingMesh() const { return boundingMesh; }

		const mat4 &getBoundsMatrix() const { return boundsMatrix; }

	protected:
		UniqueMesh *mesh;
		UniqueMesh *boundingMesh;
		mat4 boundsMatrix;

	private:
		int32 id;
		int32 shadowId;
		Type type;
	};

}


#endif //X808_LIGHT_HPP
