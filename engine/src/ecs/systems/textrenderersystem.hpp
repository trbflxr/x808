//
// Created by FLXR on 7/29/2018.
//

#ifndef X808_TEXTRENDERERSYSTEM_HPP
#define X808_TEXTRENDERERSYSTEM_HPP

#include "gfx/renderer2d.hpp"
#include "ecs/ecssystem.hpp"
#include "ecs/components/textcomponent.hpp"

namespace xe {

	class TextRendererSystem : public BaseECSSystem {
	public:
		explicit TextRendererSystem(gfx::Renderer2D *renderer) 
				: BaseECSSystem(),
				  renderer(renderer) {
			
			addComponentType(TextComponent::ID);
		}

		void updateComponents(float delta, BaseECSComponent **components) override {
			TextComponent *text = (TextComponent *) components[0];

			renderer->submitText(text);
		}

	private:
		gfx::Renderer2D *renderer;
	};

}

#endif //X808_TEXTRENDERERSYSTEM_HPP
