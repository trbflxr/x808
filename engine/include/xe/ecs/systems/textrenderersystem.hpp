//
// Created by FLXR on 7/29/2018.
//

#ifndef X808_TEXTRENDERERSYSTEM_HPP
#define X808_TEXTRENDERERSYSTEM_HPP

#include <xe/gfx/2d/textrenderer.hpp>
#include <xe/ecs/ecssystem.hpp>
#include <xe/ecs/components/textcomponent.hpp>

namespace xe {

	class TextRendererSystem : public BaseECSSystem {
	public:
		explicit TextRendererSystem(TextRenderer *renderer)
				: BaseECSSystem(),
				  renderer(renderer) {
			
			addComponentType(TextComponent::ID);
		}

		void updateComponents(float delta, BaseECSComponent **components) override {
			TextComponent *text = (TextComponent *) components[0];

			renderer->submit(text);
		}

	private:
		TextRenderer *renderer;
	};

}

#endif //X808_TEXTRENDERERSYSTEM_HPP
