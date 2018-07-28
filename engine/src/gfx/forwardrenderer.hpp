//
// Created by FLXR on 7/12/2018.
//

#ifndef X808_FORWARDRENDERER_HPP
#define X808_FORWARDRENDERER_HPP


#include "gfx/api/framebuffer.hpp"
#include "gfx/camera.hpp"
#include "gfx/lights/ambientlight.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "math/transform.hpp"
#include "resources/shadermanager.hpp"

namespace xe { namespace gfx {

	class XE_API ForwardRenderer {
	private:
		struct RenderTarget {
			const Mesh *mesh;
			const Material *material;
			const Transform &transform;

			RenderTarget(const Mesh *mesh, const Material *material, const Transform &transform) noexcept :
					mesh(mesh), material(material), transform(transform) { }
		};

	public:
		explicit ForwardRenderer(uint width, uint height, const Camera *camera, uint shadowMapSize = 0,
		                         api::Shader *shadowMapShader = GETSHADER("shadowMap"),
		                         api::Shader *defaultShader = GETSHADER("forwardAmbient"));
		~ForwardRenderer();

		inline void addLight(BaseLight *light) { lights.push_back(light); }

		void begin();
		void submit(const Mesh *mesh, const Material *material, const Transform &transform);
		void flush();

		inline const Camera *getCamera() const { return camera; }
		inline void setCamera(const Camera *camera) { ForwardRenderer::camera = camera; }

		inline AmbientLight *getAmbientLight() { return ambientLight; }
		inline const AmbientLight *getAmbientLight() const { return ambientLight; }

	private:
		void renderShadows(BaseLight *light);

	private:
		std::vector<RenderTarget> targets;
		std::vector<BaseLight *> lights;

		uint width;
		uint height;

		const Camera *camera;

		AmbientLight *ambientLight;
		ForwardRendererShader *shadowMapShader;

		bool enableShadows;
		api::FrameBuffer *shadowBuffer;
		Camera *lightCamera;

		mat4 lightMatrix;
	};

}}


#endif //X808_FORWARDRENDERER_HPP
