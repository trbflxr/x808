//
// Created by FLXR on 8/7/2018.
//

#ifndef X808_GLUNIFORMBUFFER_HPP
#define X808_GLUNIFORMBUFFER_HPP


#include "gfx/api/uniformbuffer.hpp"

namespace xe { namespace api {

	class GLUniformBuffer : public UniformBuffer {
	public:
		explicit GLUniformBuffer(Storage storage, uint bindIndex, const BufferLayout &layout, uint size);
		~GLUniformBuffer();

		void bind() override;
		void unbind() override;

		void update(const void *data, uint index, uint layoutIndex) override;

		inline uint getHandle() const override { return handle; }

	private:
		std::vector<BufferLayout> layouts;
		uint handle;
	};

}}


#endif //X808_GLUNIFORMBUFFER_HPP
