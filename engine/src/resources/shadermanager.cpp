//
// Created by FLXR on 7/22/2018.
//

#include <xe/resources/shadermanager.hpp>
#include <xe/utils/log.hpp>
#include <gfx/platform/opengl/glshadersource.hpp>

namespace xe {

	ShaderManager::ShaderManager() {
		createDefaultShaders();
	}

	ShaderManager::~ShaderManager() {
		clean();
	}

	ShaderManager &ShaderManager::instance() {
		static ShaderManager sm;
		return sm;
	}

	void ShaderManager::add(BaseShader *shader) {
		auto &&it = instance().shaders.find(shader->getName());

		if (it != instance().shaders.end()) {
			XE_ERROR(shader->getName(), " already exist!");
			return;
		}

		instance().shaders.emplace(shader->getName(), shader);
	}

	BaseShader *ShaderManager::get(const string &name) {
		auto &&it = instance().shaders.find(name);
		if (it == instance().shaders.end()) {
			XE_FATAL("Shader '", name, "' not found!");

			return nullptr;
		}

		return it->second;
	}

	void ShaderManager::clean() {
		for (auto &&shader : instance().shaders) {
			delete shader.second;
		}
	}

	void ShaderManager::createDefaultShaders() {
		using namespace internal;

		shaders.emplace("defaultBatchRenderer", new BaseShader("defaultBatchRenderer", {
				ShaderFile::fromSource(ShaderType::Vert, brVertGL, { }),
				ShaderFile::fromSource(ShaderType::Frag, brFragGL, { })
		}));
	}


}
