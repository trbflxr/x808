//
// Created by FLXR on 2/19/2019.
//

#ifndef X808_PARTICLEEFFECT_HPP
#define X808_PARTICLEEFFECT_HPP


#include <queue>
#include <xe/xeint.hpp>
#include <xe/common.hpp>
#include <xe/gfx/2d/itransformable2d.hpp>
#include <xe/gfx/particles/particle.hpp>

namespace xe {

	class Renderer2D;

	class XE_API ParticleEffect : public ITransformable2D {
	public:
		explicit ParticleEffect(float duration, float change, uint count, bool looped);
		virtual ~ParticleEffect();

		void create();

		void update(float delta);

		void play();
		void stop();

		void render(Renderer2D *renderer);

		inline bool isLooped() const { return looped; }
		inline void setLooped(bool looped) { ParticleEffect::looped = looped; }

		inline bool isFinished() const { return finished; }

		inline const Texture *getTexture() const { return texture; }
		inline void setTexture(const Texture *texture) { ParticleEffect::texture = texture; }

		inline const rect &getTextureRect() const { return textureRect; }
		inline void setTextureRect(const rect &rect) { textureRect = rect; }

		inline void setRotationStates(const std::vector<std::tuple<float, float, float>> &states) {
			rotationStates = states;
		}

		inline void setTranslationStates(const std::vector<std::tuple<float, vec2, vec2>> &states) {
			translationStates = states;
		}

		inline void setSizeStates(const std::vector<std::tuple<float, vec2, vec2>> &states) {
			sizeStates = states;
		}

		inline void setColorStates(const std::vector<std::tuple<float, vec4, vec4>> &states) {
			colorStates = states;
		}

	private:
		float duration;
		float change;

		bool looped;
		bool finished;

		uint count;

		const Texture *texture;
		rect textureRect;

		std::vector<IRenderable2D *> particles;
		std::queue<Particle *> spawnQueue;

		std::vector<std::tuple<float, float, float>> rotationStates;
		std::vector<std::tuple<float, vec2, vec2>> translationStates;
		std::vector<std::tuple<float, vec2, vec2>> sizeStates;
		std::vector<std::tuple<float, vec4, vec4>> colorStates;
	};

}


#endif //X808_PARTICLEEFFECT_HPP
