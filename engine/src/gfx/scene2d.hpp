//
// Created by FLXR on 6/30/2018.
//

#ifndef X808_SCENE_HPP
#define X808_SCENE_HPP


#include "common.hpp"
#include "components/entity.hpp"
#include "camera/orthographiccamera.hpp"
#include "renderer2d.hpp"

namespace xe{namespace gfx{

	class XE_API Scene2D {
	public:
		explicit Scene2D(const mat4 &ortho);
		~Scene2D();

		void add(Entity *entity);

		virtual void update() { }
		virtual void render(Renderer2D &renderer) { }

		void render();

		inline OrthographicCamera *getCamera() { return camera; }
		inline Renderer2D *getRenderer() { return renderer; }

	private:
		OrthographicCamera *camera;
		Renderer2D *renderer;

		std::vector<Entity *> entities;
	};

}}


#endif //X808_SCENE_HPP
