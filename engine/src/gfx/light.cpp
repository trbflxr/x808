//
// Created by FLXR on 3/3/2019.
//

#include <xe/gfx/light.hpp>

namespace xe {
	///----- Light -----///
	Light::Light(const string &name, LightType type, const Mesh *mesh) :
			ITransformable(false),
			name(name),
			type(type),
			mesh(mesh),
			enabled(true),
			shadowed(false),
			shadowId(-1),
			color(1.0f),
			intensity(0.5f),
			falloff(10.0f),
			boundsMatrix(mat4::identity()) { }

	Light::~Light() {
		delete mesh;
	}

	///----- Spot Light -----///
	SpotLight::SpotLight(const string &name) :
			Light(name, LightType::Spot, Mesh::spotLightMesh(name)),
			spotAngle(60.0f / 2.0f),
			spotBlur(0.3f) { }

	void SpotLight::update() const {
		const float spotDepth = falloff / 4.0f;
		const float spotRadius = spotDepth * tanf(to_rad(spotAngle));

		const vec3 scaler(spotRadius, spotRadius, spotDepth);
		const vec3 shifter(0.0f, 0.0f, -falloff);

		boundsMatrix = toMatrix() * (mat4::translation(shifter) * mat4::scale(scaler));

		const mat4 rotation = quat::conjugate(getRotation()).toMatrix();
		const mat4 translation = mat4::translation(-getPosition());
		view = rotation * translation;

		projection = mat4::perspective(spotAngle * 2.0f, 1.0f, 0.1f, 100.0f);
	}


	///----- Point Light -----///
	PointLight::PointLight(const string &name) :
			Light(name, LightType::Point, Mesh::pointLightMesh(name)) { }

	void PointLight::update() const {
		boundsMatrix = toMatrix() * mat4::scale(vec3(falloff));
	}


	///----- Directional Light -----///
	DirectionalLight::DirectionalLight(const string &name, const std::vector<float> &splits) :
			ITransformable(false),
			shadowed(true),
			splits(splits) {

		projection.reserve(splits.size());
		for (const auto &s : splits) {
			projection.push_back(mat4::ortho(-s, s, -s, s, -500.0f, 500.0f));
		}
	}

	void DirectionalLight::update() const {
		const mat4 rotation = quat::conjugate(getRotation()).toMatrix();
		const mat4 translation = mat4::translation(-getPosition());
		view = rotation * translation;
	}

}
