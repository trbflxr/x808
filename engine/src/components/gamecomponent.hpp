//
// Created by FLXR on 7/1/2018.
//

#ifndef X808_GAMECOMPONENT_HPP
#define X808_GAMECOMPONENT_HPP


#include "common.hpp"
#include "core/transform.hpp"
#include "core/gameobject.hpp"

namespace xe { namespace gfx {
	class RenderingEngine;

	namespace api {
		class Shader;
	}
}}


namespace xe {

	class XE_API GameComponent {
	public:
		virtual void input(const xe::TimeStep &ts) { };
		virtual void update(const xe::TimeStep &ts) { };
		virtual void render(const gfx::api::Shader *shader, const gfx::RenderingEngine *renderingEngine) { };

		inline void setBase(GameObject *base) { GameComponent::base = base; }

		inline Transform &getTransform() { return base->getTransform(); }

	private:
		GameObject *base;
	};

}


#endif //X808_GAMECOMPONENT_HPP
