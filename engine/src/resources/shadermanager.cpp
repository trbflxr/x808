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
		using namespace internal;

		shaders.emplace("defaultRenderTextureCube", api::Shader::create("defaultRenderTextureCube", {
				ShaderFile::fromSource(ShaderType::VERT, renderTextureCubeVertGL, {cameraSpatialsGL}),
				ShaderFile::fromSource(ShaderType::FRAG, renderTextureCubeFragGL, { })
		}));


		shaders.emplace("defaultBatchRenderer", api::Shader::create("defaultBatchRenderer", {
				ShaderFile::fromSource(ShaderType::VERT, brVertGL, { }),
				ShaderFile::fromSource(ShaderType::FRAG, brFragGL, { })
		}));


		//lights
		shaders.emplace("defaultForwardAmbient", api::Shader::create("defaultForwardAmbient", {
				ShaderFile::fromSource(ShaderType::VERT, forwardAmbientVertGL, { }),
				ShaderFile::fromSource(ShaderType::FRAG, forwardAmbientFragGL, {samplingGL})
		}));

		shaders.emplace("defaultForwardDirectional", api::Shader::create("defaultForwardDirectional", {
				ShaderFile::fromSource(ShaderType::VERT, forwardLightingVertGL, { }),
				ShaderFile::fromSource(ShaderType::FRAG, forwardLightingFragGL,
				                       {forwardLightingFragIncludeGL, forwardDirectionalIncludeGL, samplingGL})
		}));

		shaders.emplace("defaultForwardPoint", api::Shader::create("defaultForwardPoint", {
				ShaderFile::fromSource(ShaderType::VERT, forwardLightingVertGL, { }),
				ShaderFile::fromSource(ShaderType::FRAG, forwardLightingFragGL,
				                       {forwardLightingFragIncludeGL, forwardPointIncludeGL, samplingGL})
		}));

		shaders.emplace("defaultForwardSpot", api::Shader::create("defaultForwardSpot", {
				ShaderFile::fromSource(ShaderType::VERT, forwardLightingVertGL, { }),
				ShaderFile::fromSource(ShaderType::FRAG, forwardLightingFragGL,
				                       {forwardLightingFragIncludeGL, forwardSpotIncludeGL, samplingGL})
		}));

		//fx
		shaders.emplace("defaultFXNULL", api::Shader::create("defaultFXNULL", {
				ShaderFile::fromSource(ShaderType::VERT, fxVertGL, { }),
				ShaderFile::fromSource(ShaderType::FRAG, fxNULLFragGL, { })
		}));

		shaders.emplace("defaultFXGaussBlur", api::Shader::create("defaultFXGaussBlur", {
				ShaderFile::fromSource(ShaderType::VERT, fxVertGL, { }),
				ShaderFile::fromSource(ShaderType::FRAG, fxGaussBlur7x1FragGL, { })
		}));

		shaders.emplace("defaultFXFXAA", api::Shader::create("defaultFXFXAA", {
				ShaderFile::fromSource(ShaderType::VERT, fxVertGL, { }),
				ShaderFile::fromSource(ShaderType::FRAG, fxFXAAFragGL, { })
		}));

		//shadow map
		shaders.emplace("defaultShadowMap", api::Shader::create("defaultShadowMap", {
				ShaderFile::fromSource(ShaderType::VERT, shadowMapVertGL, { }),
				ShaderFile::fromSource(ShaderType::FRAG, shadowMapFragGL, { })
		}));

		createDefaultCommonShaders();
	}

	void ShaderManager::createDefaultCommonShaders() {
		using namespace internal;

		shaders.emplace("defaultRenderTexture1D", api::Shader::create("defaultRenderTexture1D", {
				ShaderFile::fromSource(ShaderType::VERT, commonGenericVertGL, { }),
				ShaderFile::fromSource(ShaderType::FRAG, renderTexture1DFragGL, { })
		}));

		shaders.emplace("defaultRenderTexture2D", api::Shader::create("defaultRenderTexture2D", {
				ShaderFile::fromSource(ShaderType::VERT, commonGenericVertGL, { }),
				ShaderFile::fromSource(ShaderType::FRAG, renderTexture2DFragGL, { })
		}));

		shaders.emplace("defaultRenderTexture2DArray", api::Shader::create("defaultRenderTexture2DArray", {
				ShaderFile::fromSource(ShaderType::VERT, commonGenericVertGL, { }),
				ShaderFile::fromSource(ShaderType::FRAG, renderTexture2DArrayFragGL, { })
		}));

		shaders.emplace("defaultRenderTexture3D", api::Shader::create("defaultRenderTexture3D", {
				ShaderFile::fromSource(ShaderType::VERT, commonGenericVertGL, { }),
				ShaderFile::fromSource(ShaderType::FRAG, renderTexture3DFragGL, { })
		}));

		shaders.emplace("defaultRenderTextureCube", api::Shader::create("defaultRenderTextureCube", {
				ShaderFile::fromSource(ShaderType::VERT, renderTextureCubeVertGL, {cameraSpatialsGL}),
				ShaderFile::fromSource(ShaderType::FRAG, renderTextureCubeFragGL, { })
		}));

		shaders.emplace("defaultRenderTextureCubeArray", api::Shader::create("defaultRenderTextureCubeArray", {
				ShaderFile::fromSource(ShaderType::VERT, renderTextureCubeVertGL, {cameraSpatialsGL}),
				ShaderFile::fromSource(ShaderType::FRAG, renderTextureCubeArrayFragGL, { })
		}));
	}

}
