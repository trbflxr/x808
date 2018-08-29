//
// Created by FLXR on 8/17/2018.
//

#ifndef X808_SCENERENDERER_HPP
#define X808_SCENERENDERER_HPP


#include <xe/common.hpp>
#include <xe/gfx/shader.hpp>
#include <xe/world/model/uniquemesh.hpp>
#include <xe/world/lights/light.hpp>

namespace xe {

	class XE_API SceneRenderer {
	public:
		static void drawMeshes(BeginMode mode, const std::vector<UniqueMesh *> &meshes,
		                       Shader *shader, const mat4 &transform, float delta, bool useMaterial);

		static void drawLights(BeginMode mode, const std::vector<Light *> &lights,
		                       Shader *shader, const mat4 &transform, float delta, bool displayBounds);

		static void drawLightBounds(const Light *light, Shader *shader);

	private:
		static int32 setTexture(Shader *shader, const Texture *texture, const char *sampler, const char *enable);

	private:
		static constexpr int32 enabled = 1;
		static constexpr int32 disabled = 0;
	};

}

#endif //X808_SCENERENDERER_HPP
