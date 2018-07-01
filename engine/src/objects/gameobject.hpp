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
	namespace api {
		class Shader;
	}
}}

namespace xe {

	class Application;

	class XE_API GameObject {
	public:
		virtual ~GameObject() = default;

		GameObject &addObject(GameObject *object);

		void update(const TimeStep &ts);
		void input(const TimeStep &ts);
		void render(const gfx::api::Shader *shader);

		inline Transform &getTransform() { return transform; }

	protected:
		virtual void updateInternal(const TimeStep &ts) { }
		virtual void inputInternal(const TimeStep &ts) { }
		virtual void renderInternal(const gfx::api::Shader *shader) { }

	private:
		Transform transform;
		std::vector<std::unique_ptr<GameObject>> objects;
	};

}


#endif //X808_GAMEOBJECT_HPP
