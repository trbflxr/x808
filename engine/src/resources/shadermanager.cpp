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

	void ShaderManager::add(api::Shader *shader) {
		auto &&it = instance().shaders.find(shader->getName());

		if (it != instance().shaders.end()) {
			XE_ERROR(shader->getName(), " already exist!");
			return;
		}

		instance().shaders.emplace(shader->getName(), shader);
	}

	api::Shader *ShaderManager::get(const std::string_view &name) {
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
		shaders.emplace("batchRenderer",
		                api::Shader::createFromSource("batchRenderer", batchRendererShaderSourceGL()));

		shaders.emplace("forwardAmbient",
		                api::Shader::createFromSource("forwardAmbient", forwardAmbientShaderSourceGL()));

		shaders.emplace("forwardDirectional",
		                api::Shader::createFromSource("forwardDirectional", forwardDirectionalShaderSourceGL()));

		shaders.emplace("forwardPoint",
		                api::Shader::createFromSource("forwardPoint", forwardPointShaderSourceGL()));

		shaders.emplace("forwardSpot",
		                api::Shader::createFromSource("forwardSpot", forwardSpotShaderSourceGL()));

		shaders.emplace("shadowMap",
		                api::Shader::createFromSource("shadowMap", shadowMapSourceGL()));

		shaders.emplace("filterNULL",
		                api::Shader::createFromSource("filterNULL", filterNULLSourceGL()));

		shaders.emplace("filterGaussBlur",
		                api::Shader::createFromSource("filterGaussBlur", filterGaussBlurSourceGL()));

		shaders.emplace("filterFXAA",
		                api::Shader::createFromSource("filterFXAA", filterFXAASourceGL()));
	}

}
