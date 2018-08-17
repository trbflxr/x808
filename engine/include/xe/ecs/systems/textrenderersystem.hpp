//
// Created by FLXR on 7/29/2018.
//

#ifndef X808_TEXTRENDERERSYSTEM_HPP
#define X808_TEXTRENDERERSYSTEM_HPP

#include <xe/gfx/renderer2d.hpp>
#include <xe/ecs/ecssystem.hpp>
#include <xe/ecs/components/textcomponent.hpp>

namespace xe {

	class TextRendererSystem : public BaseECSSystem {
	public:
		explicit TextRendererSystem(Renderer2D *renderer)
				: BaseECSSystem(),
				  renderer(renderer) {
			
			addComponentType(TextComponent::ID);
		}

		void updateComponents(float delta, BaseECSComponent **components) override {
			TextComponent *text = (TextComponent *) components[0];

			renderer->submitText(text);
		}

	private:
		Renderer2D *renderer;
	};

}

#endif //X808_TEXTRENDERERSYSTEM_HPP
