//
// Created by FLXR on 7/9/2018.
//

#ifndef X808_MATERIAL_HPP
#define X808_MATERIAL_HPP


#include <vector>
#include <map>
#include <string>
#include "xeint.hpp"
#include "common.hpp"
#include "utils/log.hpp"
#include "gfx/api/shader.hpp"
#include "gfx/api/texture.hpp"
#include "gfx/api/shaderuniform.hpp"

namespace xe { namespace gfx {

	class XE_API Material {
	private:
		friend class MaterialInstance;

	public:
		enum class RenderFlags {
			NONE = 0,
			DISABLE_DEPTH_TEST = BIT(0),
			WIREFRAME = BIT(1)
		};

	public:
		explicit Material(api::Shader *shader);
		~Material();

		void bind();
		void unbind();

		void setUniformData(const std::string_view &uniform, byte *data);
		void setTexture(const std::string_view &name, api::Texture *texture);

		inline uint getRenderFlags() const { return renderFlags; }
		inline void setRenderFlags(uint flags) { renderFlags = flags; }
		inline void setRenderFlag(RenderFlags flag) { renderFlags |= (uint) flag; }

		inline api::Shader *getShader() { return shader; }

		template<typename T>
		void setUniform(const std::string_view &name, const T &data) {
			byte *buffer;
			api::ShaderUniform *declaration = findUniform(name, &buffer);
			if (!declaration) {
				XE_ERROR("Could not find uniform with name '", name, "'!");
				return;
			}
			memcpy(buffer + declaration->getOffset(), &data, declaration->getSize());
		}

	protected:
		void allocateStorage();
		api::ShaderUniform *findUniform(const std::string_view &name, byte **outBuffer = nullptr);
		api::ShaderResource *findResource(const std::string_view &name);

	protected:
		api::Shader *shader;

		byte *vsUserUniformBuffer;
		uint vsUserUniformBufferSize;

		byte *fsUserUniformBuffer;
		uint fsUserUniformBufferSize;

		std::vector<api::Texture *> textures;

		const api::ShaderUniformVec *vsUserUniforms;
		const api::ShaderUniformVec *fsUserUniforms;
		const api::ShaderResourceVec *resources;

		uint renderFlags;
	};


	///-------- MaterialInstance --------///
	class XE_API MaterialInstance {
	public:
		explicit MaterialInstance(Material *material);

		inline Material *getMaterial() const { return material; }

		void bind();
		void unbind();

		void setUniformData(const std::string_view &uniform, byte *data);
		void setTexture(const std::string_view &name, api::Texture *texture);

		inline int getRenderFlags() const { return renderFlags; }
		inline void setRenderFlags(int flags) { renderFlags = flags; }
		inline void setRenderFlag(Material::RenderFlags flag) { renderFlags |= (int) flag; }

		template<typename T>
		void setUniform(const std::string_view &name, const T &data) {
			byte *buffer;
			api::ShaderUniform *declaration = findUniform(name, &buffer);
			XE_ASSERT(declaration);
			memcpy(buffer + declaration->getOffset(), &data, declaration->getSize());
		}

	private:
		void allocateStorage();
		api::ShaderUniform *findUniform(const std::string_view &name, byte **outBuffer = nullptr);
		api::ShaderResource *findResource(const std::string_view &name);

	private:
		Material *material;

		byte *vsUserUniformBuffer;
		uint vsUserUniformBufferSize;

		byte *fsUserUniformBuffer;
		uint fsUserUniformBufferSize;

		std::vector<api::Texture *> textures;

		const api::ShaderUniformVec *vsUserUniforms;
		const api::ShaderUniformVec *fsUserUniforms;
		const api::ShaderResourceVec *resources;

		int renderFlags;
	};

}}


#endif //X808_MATERIAL_HPP
