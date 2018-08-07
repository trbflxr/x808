//
// Created by FLXR on 8/4/2018.
//

#ifndef X808_IRENDERER3D_HPP
#define X808_IRENDERER3D_HPP


#include "camera.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "math/transform.hpp"

namespace xe {

	class IRenderer3D {
	protected:
		struct RenderTarget {
			const Mesh *mesh;
			const Material *material;
			const Transform &transform;

			RenderTarget(const Mesh *mesh, const Material *material, const Transform &transform) noexcept :
					mesh(mesh), material(material), transform(transform) { }
		};

	public:
		virtual void begin() = 0;
		virtual void submit(const Mesh *mesh, const Material *material, const Transform &transform) = 0;
		virtual void flush() = 0;

		inline const Camera *getCamera() const { return camera; }
		inline Camera *getCamera() { return camera; }

		inline void setCamera(Camera *camera) { IRenderer3D::camera = camera; }

	protected:
		explicit IRenderer3D(uint width, uint height, Camera *camera) :
				width(width),
				height(height),
				camera(camera) { }

	protected:
		uint width;
		uint height;

		Camera *camera;
	};

}


#endif //X808_IRENDERER3D_HPP
