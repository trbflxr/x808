//
// Created by FLXR on 7/22/2018.
//

#include "shadermanager.hpp"
#include "utils/log.hpp"
#include "platform/opengl/glshadersource.hpp"

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

	void ShaderManager::add(gfx::api::Shader *shader) {
		auto &&it = instance().shaders.find(shader->getName());

		if (it != instance().shaders.end()) {
			XE_ERROR(shader->getName(), " already exist!");
			return;
		}

		instance().shaders.emplace(shader->getName(), shader);
	}

	gfx::api::Shader *ShaderManager::get(const std::string_view &name) {
		auto &&it = instance().shaders.find(name.data());
		if (it == instance().shaders.end()) {
			XE_FATAL("Shader '", name, "' not found!");

			return nullptr;
		}

		return it->second;
	}

	void ShaderManager::clean() {
		instance().shaders.clear();
	}

	void ShaderManager::createDefaultShaders() {
		using namespace gfx::api;

		shaders.emplace("batchRenderer",
		                Shader::createFromSource("batchRenderer", gfx::batchRendererShaderSourceGL()));

		shaders.emplace("forwardAmbient",
		                Shader::createFromSource("forwardAmbient", gfx::forwardAmbientShaderSourceGL()));

		shaders.emplace("forwardDirectional",
		                Shader::createFromSource("forwardDirectional", gfx::forwardDirectionalShaderSourceGL()));

		shaders.emplace("forwardPoint",
		                Shader::createFromSource("forwardPoint", gfx::forwardPointShaderSourceGL()));

		shaders.emplace("forwardSpot",
		                Shader::createFromSource("forwardSpot", gfx::forwardSpotShaderSourceGL()));

		shaders.emplace("shadowMap",
		                Shader::createFromSource("shadowMap", gfx::shadowMapSourceGL()));

		shaders.emplace("filterNULL",
		                Shader::createFromSource("filterNULL", gfx::filterNULLSourceGL()));

		shaders.emplace("filterGaussBlur",
		                Shader::createFromSource("filterGaussBlur", gfx::filterGaussBlurSourceGL()));

		shaders.emplace("filterFXAA",
		                Shader::createFromSource("filterFXAA", gfx::filterFXAASourceGL()));
	}

}
