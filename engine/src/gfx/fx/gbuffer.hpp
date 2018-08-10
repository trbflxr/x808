//
// Created by FLXR on 8/9/2018.
//

#ifndef X808_GBUFFER_HPP
#define X808_GBUFFER_HPP


#include "gfx/api/texture.hpp"
#include "gfx/api/shader.hpp"
#include "gfx/api/framebuffer.hpp"
#include "rendereffect.hpp"

namespace xe { namespace fx {

	class XE_API GBuffer : public RenderEffect {
	public:
		explicit GBuffer(uint width, uint height);

		void load() override;
		void unload() override { }
		void reload() override { }

		void toggleWireframe();

	protected:
		void loadPrograms() override;
		void loadBuffers() override;

	private:

	};

}}


#endif //X808_GBUFFER_HPP
