//
// Created by FLXR on 7/25/2018.
//

#ifndef X808_MODELRENDERERSYSTEM_HPP
#define X808_MODELRENDERERSYSTEM_HPP


#include "ecs/ecssystem.hpp"
#include "ecs/components/transformcomponent.hpp"
#include "ecs/components/modelcomponent.hpp"
#include "gfx/forwardrenderer.hpp"

namespace xe {

	class ForwardRendererSystem : public BaseECSSystem {
	public:
		explicit ForwardRendererSystem(ForwardRenderer *renderer) :
				BaseECSSystem(),
				renderer(renderer) {

			addComponentType(ModelComponent::ID);
			addComponentType(TransformComponent::ID);
		}

		void updateComponents(float delta, BaseECSComponent **components) override {
			ModelComponent *model = (ModelComponent *) components[0];
			TransformComponent *transform = (TransformComponent *) components[1];

			renderer->submit(model->mesh, model->material, transform->transform);
		}

	private:
		ForwardRenderer *renderer;
	};

}


#endif //X808_MODELRENDERERSYSTEM_HPP
