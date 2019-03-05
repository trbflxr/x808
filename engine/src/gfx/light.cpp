//
// Created by FLXR on 3/3/2019.
//

#include <xe/gfx/light.hpp>

namespace xe {
	///----- Light -----///
	Light::Light(const string &name, LightType type, const Mesh *mesh) :
			name(name),
			type(type),
			mesh(mesh),
			enabled(true),
			shadowed(true),
			color(1.0f),
			intensity(0.5f),
			falloff(10.0f),
			boundsMatrix(mat4::identity()) { }

	///----- Spot Light -----///
	SpotLight::SpotLight(const string &name, const Mesh *mesh) :
			Light(name, LightType::Spot, mesh),
			spotAngle(60.0f / 2.0f),
			spotBlur(0.3f) {

		update();
	}

	void SpotLight::update() {
		const float spotDepth = falloff / 4.0f;
		const float spotRadius = spotDepth * tanf(to_rad(spotAngle));

		const vec3 scaler(spotRadius, spotRadius, spotDepth);
		const vec3 shifter(0.0f, 0.0f, -falloff);

		boundsMatrix = mat4::translation(shifter) * mat4::scale(scaler);
	}

	///----- Point Light -----///
	PointLight::PointLight(const string &name, const Mesh *mesh) :
			Light(name, LightType::Point, mesh) {

		update();
	}

	void PointLight::update() {
		const float pointRadius = falloff;
		const vec3 scaler(pointRadius, pointRadius, pointRadius);

		boundsMatrix = mat4::scale(scaler);
	}

	///----- Directiona lLight -----///
	DirectionalLight::DirectionalLight(const string &name,  bool shadow) :
			Light(name, LightType::Directional, nullptr) {

		falloff = 0.0f;
		shadowed = shadow;
		update();
	}

	void DirectionalLight::update() {

	}

}
