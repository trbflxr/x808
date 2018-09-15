//
// Created by FLXR on 7/8/2018.
//

#ifndef X808_SPRITERENDERERSYSTEM_HPP
#define X808_SPRITERENDERERSYSTEM_HPP


#include <xe/gfx/2d/batchrenderer2d.hpp>
#include <xe/ecs/ecssystem.hpp>
#include <xe/ecs/components/spritecomponent.hpp>

namespace xe {

	class SpriteRendererSystem : public BaseECSSystem {
	public:
		explicit SpriteRendererSystem(BatchRenderer2D *renderer) :
				BaseECSSystem(),
				renderer(renderer) {

			addComponentType(SpriteComponent::ID);
		}

		void updateComponents(float delta, BaseECSComponent **components) override {
			SpriteComponent *sprite = (SpriteComponent *) components[0];

			renderer->submit(sprite->sprite);
		}

	private:
		BatchRenderer2D *renderer;
	};

}


#endif //X808_SPRITERENDERERSYSTEM_HPP
