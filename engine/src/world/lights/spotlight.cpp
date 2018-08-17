//
// Created by FLXR on 8/13/2018.
//

#include <xe/world/lights/spotlight.hpp>

namespace xe {

	SpotLight::SpotLight(const string &id, const vec3 &color, float intensity, float falloff,
	                     float spotAngle, float spotBlur, bool shadow, Mesh *mesh, const mat4 &transformation) :
			Light(id, Type::Spot, color, intensity, falloff, shadow, transformation),
			spotAngle(spotAngle / 2.0f),
			spotBlur(spotBlur) {

		SpotLight::mesh = new UniqueMesh(id, mesh, transformation);

		float spotDepth = falloff / 2.0f;
		float spotRadius = spotDepth * tanf(spotAngle) * 2.0f;

		vec3 scaler(spotRadius, spotRadius, spotDepth);
		vec3 shifter(0.0f, 0.0f, -scaler.z);

		boundsMatrix = mat4::scale(scaler) * mat4::translation(shifter);
		mat4 t = boundsMatrix * transformation.clearScale();

		string boundsId(id);
		boundsId.append("-bounds");
		boundingMesh = new UniqueMesh(boundsId, mesh, t);

		spatial.setPerspective(to_deg(spotAngle * 2.0f), 1.0f, 0.1f, 100.0f);
	}

	mat4 SpotLight::getShadowViewMatrix() const {
		return mat4::translation(-spatial.position) * mat4::transpose(spatial.getRotationMatrix());
	}

	mat4 SpotLight::getShadowPerspectiveMatrix() const {
		return spatial.getPerspective();
	}

	mat4 SpotLight::getViewRayMatrix() const {
		return mat4::invert(getShadowViewMatrix().clearTranslation() * getShadowPerspectiveMatrix());
	}

}