//
// Created by FLXR on 7/9/2018.
//

#include "material.hpp"

namespace xe { namespace gfx {


	Material::Material(api::Shader *shader) :
			shader(shader),
			vsUserUniformBuffer(nullptr),
			vsUserUniformBufferSize(0),
			fsUserUniformBuffer(nullptr),
			fsUserUniformBufferSize(0),
			vsUserUniforms(nullptr),
			fsUserUniforms(nullptr) {

		allocateStorage();
		resources = &shader->getResources();
	}

	Material::~Material() {
		delete[]vsUserUniformBuffer;
		delete[]fsUserUniformBuffer;
	}

	void Material::bind() {
		shader->bind();

		//todo: don't do this if not use
		if (vsUserUniformBuffer) {
			shader->setVSUserUniformBuffer(vsUserUniformBuffer, vsUserUniformBufferSize);
		}
		if (fsUserUniformBuffer) {
			shader->setFSUserUniformBuffer(fsUserUniformBuffer, fsUserUniformBufferSize);
		}

		for (uint i = 0; i < textures.size(); ++i) {
			if (textures[i]) {
				textures[i]->bind(i);
			}
		}
	}

	void Material::unbind() {
		for (uint i = 0; i < textures.size(); ++i) {
			if (textures[i]) {
				textures[i]->unbind(i);
			}
		}
	}

	void Material::setUniformData(const std::string_view &uniform, byte *data) {
		byte *buffer;
		api::ShaderUniform *decl = findUniform(uniform, &buffer);
		memcpy(buffer + decl->getOffset(), data, decl->getSize());
	}

	void Material::setTexture(const std::string_view &name, api::Texture *texture) {
		api::ShaderResource *resource = findResource(name);
		if (!resource) {
			XE_FATAL("ShaderUniform is nullptr");
			XE_ASSERT(false);
		}

		uint slot = resource->getRegister();
		if (textures.size() <= slot) {
			textures.resize(slot + 1);
		}
		textures[slot] = texture;
	}

	void Material::allocateStorage() {
		const api::ShaderUniformBuffer *vsBuffer = shader->getVSUserUniformBuffer();
		if (vsBuffer) {
			vsUserUniformBufferSize = vsBuffer->getSize();
			vsUserUniformBuffer = new byte[vsUserUniformBufferSize];

			memset(vsUserUniformBuffer, 0, vsUserUniformBufferSize);
			vsUserUniforms = &vsBuffer->getUniforms();
		}

		const api::ShaderUniformBuffer *fsBuffer = shader->getFSUserUniformBuffer();
		if (fsBuffer) {
			fsUserUniformBufferSize = fsBuffer->getSize();
			fsUserUniformBuffer = new byte[fsUserUniformBufferSize];

			memset(fsUserUniformBuffer, 0, fsUserUniformBufferSize);
			fsUserUniforms = &fsBuffer->getUniforms();
		}
	}

	api::ShaderUniform *Material::findUniform(const std::string_view &name, byte **outBuffer) {
		if (vsUserUniforms) {
			for (auto &&uniform : *vsUserUniforms) {
				if (uniform->getName() == name) {
					*outBuffer = vsUserUniformBuffer;
					return uniform;
				}
			}
		}
		if (fsUserUniforms) {
			for (auto &&uniform : *fsUserUniforms) {
				if (uniform->getName() == name) {
					*outBuffer = fsUserUniformBuffer;
					return uniform;
				}
			}
		}
		return nullptr;
	}

	api::ShaderResource *Material::findResource(const std::string_view &name) {
		for (auto &&resource : *resources) {
			if (resource->getName() == name) {
				return resource;
			}
		}
		return nullptr;
	}

	///-------- MaterialInstance --------///
	MaterialInstance::MaterialInstance(Material *material) :
			material(material) {

		allocateStorage();
		memcpy(vsUserUniformBuffer, material->vsUserUniformBuffer, vsUserUniformBufferSize);
		memcpy(fsUserUniformBuffer, material->fsUserUniformBuffer, fsUserUniformBufferSize);

		resources = material->resources;
		renderFlags = material->renderFlags;
	}

	void MaterialInstance::bind() {
		material->bind();

		//todo: don't do this if not use
		if (vsUserUniformBuffer) {
			material->shader->setVSUserUniformBuffer(vsUserUniformBuffer, vsUserUniformBufferSize);
		}
		if (fsUserUniformBuffer) {
			material->shader->setFSUserUniformBuffer(fsUserUniformBuffer, fsUserUniformBufferSize);
		}

		for (uint i = 0; i < textures.size(); ++i) {
			if (textures[i]) {
				textures[i]->bind(i);
			}
		}
	}

	void MaterialInstance::unbind() {
		material->unbind();

		for (uint i = 0; i < textures.size(); ++i) {
			if (textures[i]) {
				textures[i]->unbind(i);
			}
		}
	}

	void MaterialInstance::setUniformData(const std::string_view &uniform, byte *data) {
		byte *buffer;
		api::ShaderUniform *decl = findUniform(uniform, &buffer);
		if (!buffer) {
			XE_FATAL("buffers is nullptr");
			XE_ASSERT(false);
		}
		memcpy(buffer + decl->getOffset(), data, decl->getSize());
	}

	void MaterialInstance::setTexture(const std::string_view &name, api::Texture *texture) {
		api::ShaderResource *resource = findResource(name);
		if (!resource) {
			XE_FATAL("ShaderUniform is nullptr");
			XE_ASSERT(false);
		}
		uint slot = resource->getRegister();

		if (textures.size() <= slot) {
			textures.resize(slot + 1);
		}
		textures[slot] = texture;
	}

	void MaterialInstance::allocateStorage() {
		const api::ShaderUniformBuffer *vsBuffer = material->shader->getVSUserUniformBuffer();
		if (vsBuffer) {
			vsUserUniformBufferSize = vsBuffer->getSize();
			vsUserUniformBuffer = new byte[vsUserUniformBufferSize];

			memset(vsUserUniformBuffer, 0, vsUserUniformBufferSize);
			vsUserUniforms = &vsBuffer->getUniforms();
		}

		const api::ShaderUniformBuffer *fsBuffer = material->shader->getFSUserUniformBuffer();
		if (fsBuffer) {
			fsUserUniformBufferSize = fsBuffer->getSize();
			fsUserUniformBuffer = new byte[fsUserUniformBufferSize];

			memset(fsUserUniformBuffer, 0, fsUserUniformBufferSize);
			fsUserUniforms = &fsBuffer->getUniforms();
		}
	}

	api::ShaderUniform *MaterialInstance::findUniform(const std::string_view &name, byte **outBuffer) {
		if (vsUserUniforms) {
			for (auto &&uniform : *vsUserUniforms) {
				if (uniform->getName() == name) {
					*outBuffer = vsUserUniformBuffer;
					return uniform;
				}
			}
		}
		if (fsUserUniforms) {
			for (auto &&uniform : *fsUserUniforms) {
				if (uniform->getName() == name) {
					*outBuffer = fsUserUniformBuffer;
					return uniform;
				}
			}
		}
		return nullptr;
	}

	api::ShaderResource *MaterialInstance::findResource(const std::string_view &name) {
		for (auto &&resource : *resources) {
			if (resource->getName() == name) {
				return resource;
			}
		}
		return nullptr;
	}

}}