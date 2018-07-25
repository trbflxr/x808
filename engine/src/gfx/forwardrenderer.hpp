//
// Created by FLXR on 7/12/2018.
//

#ifndef X808_FORWARDRENDERER_HPP
#define X808_FORWARDRENDERER_HPP


#include "gfx/api/framebuffer.hpp"
#include "gfx/camera/camera.hpp"
#include "gfx/lights/ambientlight.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "math/transform.hpp"

#include "ecs/components/spritecomponent.hpp"

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
		explicit ForwardRenderer(uint width, uint height, uint shadowMapSize, const Camera *camera);
		~ForwardRenderer();

		inline void setAmbientLight(AmbientLight *light) { ambientLight = light; }
		inline void addLight(BaseLight *light) { lights.push_back(light); }

		void begin();
		void submit(const Mesh *mesh, const Material *material, const Transform &transform);
		void flush(SpriteComponent *s);

		inline const Camera *getCamera() const { return camera; }
		inline void setCamera(const Camera *camera) { ForwardRenderer::camera = camera; }

	private:
		std::vector<RenderTarget> targets;

		std::vector<BaseLight *> lights;
		AmbientLight *ambientLight;

		uint width;
		uint height;

		const Camera *camera;

		bool enableShadows;
		api::FrameBuffer *shadowBuffer;
	};

}}


#endif //X808_FORWARDRENDERER_HPP
