//
// Created by FLXR on 7/1/2018.
//

#ifndef X808_GAMEOBJECT_HPP
#define X808_GAMEOBJECT_HPP


#include <vector>
#include <memory>
#include "common.hpp"
#include "transform.hpp"
#include "utils/timestep.hpp"

namespace xe { namespace gfx {
	class RenderingEngine;

	namespace api {
		class Shader;
	}
}}

namespace xe {

	class Application;

	class GameComponent;

	class XE_API GameObject {
	public:
		explicit GameObject(Application* app);
		virtual ~GameObject() = default;

		GameObject &addObject(GameObject *object);
		GameObject &addComponent(GameComponent *component);

		void update(const TimeStep &ts);
		void input(const TimeStep &ts);

		void render(const gfx::api::Shader *shader, const gfx::RenderingEngine *renderingEngine) const;

		inline Transform &getTransform() { return transform; }

	private:
		Transform transform;
		Application* application;
		std::vector<std::unique_ptr<GameObject>> objects;
		std::vector<std::unique_ptr<GameComponent>> components;
	};

}


#endif //X808_GAMEOBJECT_HPP
