//
// Created by FLXR on 8/13/2018.
//

#ifndef X808_LIGHT_HPP
#define X808_LIGHT_HPP


#include <xe/gameobject.hpp>
#include <xe/math/transform.hpp>
#include <xe/world/model/uniquemesh.hpp>

namespace xe {

	class Light : public GameObject {
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
		float falloff;

	public:
		explicit Light(const string &id, Type type, const vec3 &color, float intensity, float falloff, bool shadow,
		               const mat4 &transformation, Mesh *mesh) :
				GameObject(transformation),
				name(id),
				id(-1),
				shadowId(-1),
				enabled(false),
				type(type),
				color(color),
				intensity(intensity),
				falloff(falloff),
				shadowed(shadow),
				boundsMatrix(mat4::identity()),
				mesh(mesh) { }

		virtual ~Light() {
			delete mesh;
		}

		inline const string &getName() const { return name; }
		inline int32 getLightId() const { return id; }
		inline int32 getShadowId() const { return shadowId; }
		inline Type getType() const { return type; }

		inline Mesh *getMesh() const { return mesh; }

		inline const mat4 &getBoundsMatrix() const { return boundsMatrix; }

	protected:
		Mesh *mesh;
		mat4 boundsMatrix;

	private:
		string name;
		int32 id;
		int32 shadowId;
		Type type;
	};

}


#endif //X808_LIGHT_HPP
