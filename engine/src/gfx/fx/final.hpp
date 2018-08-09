//
// Created by FLXR on 8/8/2018.
//

#ifndef X808_FINAL_HPP
#define X808_FINAL_HPP


#include "common.hpp"
#include "rendereffect.hpp"
#include "quad.hpp"
#include "gfx/api/shader.hpp"
#include "gfx/api/framebuffer.hpp"

namespace xe { namespace fx {

	class XE_API Final : public RenderEffect {
	public:
		explicit Final(uint width, uint height);
		~Final();

		void load() override;
		void unload() override { }
		void reload() override { }

		void render(Quad *quad);

		api::Texture *getTexture() { return finalTexture; }
		api::FrameBuffer *getFrameBuffer() { return finalFBO; }

	protected:
		void loadPrograms() override;
		void loadBuffers() override;

	private:
		api::Shader *finalShader;
		api::FrameBuffer *finalFBO;
		api::Texture *finalTexture;
	};

}}


#endif //X808_FINAL_HPP
