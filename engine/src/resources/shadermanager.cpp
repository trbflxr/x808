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

	void ShaderManager::add(api::BaseShader *shader) {
		auto &&it = instance().shaders.find(shader->getName());

		if (it != instance().shaders.end()) {
			XE_ERROR(shader->getName(), " already exist!");
			return;
		}

		instance().shaders.emplace(shader->getName(), shader);
	}

	api::BaseShader *ShaderManager::get(const std::string_view &name) {
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
		using namespace internal;

		shaders.emplace("defaultBatchRenderer", api::BaseShader::create("defaultBatchRenderer", {
				ShaderFile::fromSource(ShaderType::Vert, brVertGL, { }),
				ShaderFile::fromSource(ShaderType::Frag, brFragGL, { })
		}));

		//lights
		shaders.emplace("defaultForwardAmbient", api::BaseShader::create("defaultForwardAmbient", {
				ShaderFile::fromSource(ShaderType::Vert, forwardAmbientVertGL, { }),
				ShaderFile::fromSource(ShaderType::Frag, forwardAmbientFragGL, {samplingGL})
		}));

		shaders.emplace("defaultForwardDirectional", api::BaseShader::create("defaultForwardDirectional", {
				ShaderFile::fromSource(ShaderType::Vert, forwardLightingVertGL, { }),
				ShaderFile::fromSource(ShaderType::Frag, forwardLightingFragGL,
				                       {forwardLightingFragIncludeGL, forwardDirectionalIncludeGL, samplingGL})
		}));

		shaders.emplace("defaultForwardPoint", api::BaseShader::create("defaultForwardPoint", {
				ShaderFile::fromSource(ShaderType::Vert, forwardLightingVertGL, { }),
				ShaderFile::fromSource(ShaderType::Frag, forwardLightingFragGL,
				                       {forwardLightingFragIncludeGL, forwardPointIncludeGL, samplingGL})
		}));

		shaders.emplace("defaultForwardSpot", api::BaseShader::create("defaultForwardSpot", {
				ShaderFile::fromSource(ShaderType::Vert, forwardLightingVertGL, { }),
				ShaderFile::fromSource(ShaderType::Frag, forwardLightingFragGL,
				                       {forwardLightingFragIncludeGL, forwardSpotIncludeGL, samplingGL})
		}));

		//shadow map
		shaders.emplace("defaultShadowMap", api::BaseShader::create("defaultShadowMap", {
				ShaderFile::fromSource(ShaderType::Vert, shadowMapVertGL, { }),
				ShaderFile::fromSource(ShaderType::Frag, shadowMapFragGL, { })
		}));


		//fx
		shaders.emplace("defaultFinalFX", api::BaseShader::create("defaultFinalFX", {
				ShaderFile::fromSource(ShaderType::Vert, commonGenericVertGL, { }),
				ShaderFile::fromSource(ShaderType::Frag, finalSceneFragGL, {fxaaIncludeGL})
		}));

		shaders.emplace("defaultGaussBlur7x1FX", api::BaseShader::create("defaultGaussBlur7x1FX", {
				ShaderFile::fromSource(ShaderType::Vert, commonGenericVertGL, { }),
				ShaderFile::fromSource(ShaderType::Frag, fxGaussBlur7x1FragGL, { })
		}));
	}


}
