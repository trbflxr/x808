//
// Created by FLXR on 7/22/2018.
//

#include <xetools/spak.hpp>
#include <xe/utils/log.hpp>
#include <xe/gfx/context.hpp>
#include <xe/resources/shadermanager.hpp>

namespace xe {

	ShaderManager::ShaderManager() {
		sources = spak::unpack("pack001.pak");

		createDefaultShaders();
	}

	ShaderManager::~ShaderManager() {
		clean();
	}

	void ShaderManager::init() {
		instance();
	}

	ShaderManager &ShaderManager::instance() {
		static ShaderManager sm;
		return sm;
	}

	bool ShaderManager::add(Shader *shader) {
		auto &&it = instance().shaders.find(shader->getName());

		if (it != instance().shaders.end()) {
			XE_CORE_ERROR("[ShaderManager]: shader '{0}' already exist and be deleted", shader->getName());

			delete shader;
			return false;
		}

		instance().shaders.emplace(shader->getName(), shader);
		return true;
	}

	const Shader *ShaderManager::get(const string &name) {
		auto &&it = instance().shaders.find(name);
		if (it == instance().shaders.end()) {
			XE_CORE_FATAL("[ShaderManager]: shader '{0}' not found!", name);

			return nullptr;
		}

		return it->second;
	}

	const string &ShaderManager::getSource(const string &name) {
		static string empty;

		auto &&it = instance().sources.find(name);
		if (it == instance().sources.end()) {
			XE_CORE_FATAL("[ShaderManager]: source '{0}' not found!", name);
			return empty;
		}

		return it->second;
	}

	void ShaderManager::clean() {
		for (auto &&shader : instance().shaders) {
			delete shader.second;
		}
	}

	void ShaderManager::createDefaultShaders() {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OpenGL : createGLShaders();
				break;

			default: XE_CORE_FATAL("[ShaderManager]: selected render API is not supported");
				break;
		}
	}

	void ShaderManager::createGLShaders() {
		auto node = sources.extract("renderTexture2D_vert");
		node.key() = "commonGeneric_vert";
		sources.insert(std::move(node));

		//2d
		shaders.emplace("dRenderer2D", new Shader("dRenderer2D", {
				ShaderFile::fromSource(ShaderType::Vert, sources["renderer2D_vert"]),
				ShaderFile::fromSource(ShaderType::Frag, sources["renderer2D_frag"])
		}));

		shaders.emplace("dTextRenderer", new Shader("dTextRenderer", {
				ShaderFile::fromSource(ShaderType::Vert, sources["textRenderer_vert"]),
				ShaderFile::fromSource(ShaderType::Frag, sources["textRenderer_frag"])
		}));


		///gl420 shaders
		if (Context::getRenderAPIVersion() >= 420) {
			///----- final fx shader -----///
			shaders.emplace("dFinalFX", new Shader("dFinalFX", {
					ShaderFile::fromSource(ShaderType::Vert, sources["commonGeneric_vert"]),
					ShaderFile::fromSource(ShaderType::Frag, sources["finalScene_frag"],
					                       {sources["fxaa_include"]})
			}));


			///----- gbuffer shaders -----///
			//includes
			const std::vector<string> geomInclude{sources["1_cameraSpatials_ubo"],
			                                      sources["gBufferFunctions_include"],
			                                      sources["linearDepth_include"]};

			const std::vector<string> lightingInclude{sources["1_cameraSpatials_ubo"],
			                                          sources["lightingFunctions_include"],
			                                          sources["positionFromDepth_include"],
			                                          sources["linearDepth_include"]};

			//gbuffer geometry shader
			shaders.emplace("dGeomShader", new Shader("dGeomShader", {
					ShaderFile::fromSource(ShaderType::Vert, sources["geometry_vert"]),

					ShaderFile::fromSource(ShaderType::TessControl, sources["gBufferGeometry_tesc"],
					                       {sources["1_cameraSpatials_ubo"], sources["culling_include"]}),

					ShaderFile::fromSource(ShaderType::TessEval, sources["gBufferGeometry_tese"]),

					ShaderFile::fromSource(ShaderType::Geom, sources["gBufferGeometry_geom"],
					                       {sources["1_cameraSpatials_ubo"]}),

					ShaderFile::fromSource(ShaderType::Frag, sources["gBufferGeometry_frag"],
					                       {geomInclude})
			}));


			//gbuffer stencil shader
			shaders.emplace("dStencil", new Shader("dStencil", {
					ShaderFile::fromSource(ShaderType::Vert, sources["gBufferStencil_vert"],
					                       {sources["1_cameraSpatials_ubo"]})
			}));


			//gbuffer spot light shader
			shaders.emplace("dSpotLight", new Shader("dSpotLight", {
					ShaderFile::fromSource(ShaderType::Vert, sources["gBufferStencil_vert"],
					                       {sources["1_cameraSpatials_ubo"]}),

					ShaderFile::fromSource(ShaderType::Frag, sources["gBufferLightingSpot_frag"],
					                       {lightingInclude})
			}));


			//gbuffer point light shader
			shaders.emplace("dPointLight", new Shader("dPointLight", {
					ShaderFile::fromSource(ShaderType::Vert, sources["gBufferStencil_vert"],
					                       {sources["1_cameraSpatials_ubo"]}),

					ShaderFile::fromSource(ShaderType::Frag, sources["gBufferLightingPoint_frag"],
					                       {lightingInclude})
			}));


			//gbuffer light accumulation shader
			shaders.emplace("dAccumulation", new Shader("dAccumulation", {
					ShaderFile::fromSource(ShaderType::Vert, sources["commonGeneric_vert"]),
					ShaderFile::fromSource(ShaderType::Frag, sources["gBufferAccumulation_frag"])
			}));


			///----- render texture shaders -----///
			//render texture 1d
			shaders.emplace("dRenderTexture1D", new Shader("dRenderTexture1D", {
					ShaderFile::fromSource(ShaderType::Vert, sources["commonGeneric_vert"]),
					ShaderFile::fromSource(ShaderType::Frag, sources["renderTexture1D_frag"])
			}));


			//render texture 2d
			shaders.emplace("dRenderTexture2D", new Shader("dRenderTexture2D", {
					ShaderFile::fromSource(ShaderType::Vert, sources["commonGeneric_vert"]),
					ShaderFile::fromSource(ShaderType::Frag, sources["renderTexture2D_frag"])
			}));


			//render texture 2d array
			shaders.emplace("dRenderTexture2DArray", new Shader("dRenderTexture2DArray", {
					ShaderFile::fromSource(ShaderType::Vert, sources["commonGeneric_vert"]),
					ShaderFile::fromSource(ShaderType::Frag, sources["renderTexture2DArray_frag"])
			}));


			//render texture 3d
			shaders.emplace("dRenderTexture3D", new Shader("dRenderTexture3D", {
					ShaderFile::fromSource(ShaderType::Vert, sources["commonGeneric_vert"]),
					ShaderFile::fromSource(ShaderType::Frag, sources["renderTexture3D_frag"])
			}));


			//render texture cube
			shaders.emplace("dRenderTextureCube", new Shader("dRenderTextureCube", {
					ShaderFile::fromSource(ShaderType::Vert, sources["renderTextureCube_vert"],
					                       {sources["1_cameraSpatials_ubo"]}),
					ShaderFile::fromSource(ShaderType::Frag, sources["renderTextureCube_frag"])
			}));


			//render texture cube array
			shaders.emplace("dRenderTextureCubeArray", new Shader("dRenderTextureCubeArray", {
					ShaderFile::fromSource(ShaderType::Vert, sources["renderTextureCube_vert"],
					                       {sources["1_cameraSpatials_ubo"]}),
					ShaderFile::fromSource(ShaderType::Frag, sources["renderTextureCubeArray_frag"])
			}));
		}

		///gl430 shaders
		if (Context::getRenderAPIVersion() >= 430) {
			///----- hdr shaders -----///
			//luminosity
			shaders.emplace("dAccumulation", new Shader("dLuminosity", {
					ShaderFile::fromSource(ShaderType::Compute, sources["hdrLuminosity_comp"])
			}));


			//autoExposure
			shaders.emplace("dAutoExposure", new Shader("dAutoExposure", {
					ShaderFile::fromSource(ShaderType::Compute, sources["hdrAutoExposure_comp"],
					                       {sources["interpolation_include"]})
			}));


			//Luminosity
			shaders.emplace("dScaleScene", new Shader("dScaleScene", {
					ShaderFile::fromSource(ShaderType::Vert, sources["commonGeneric_vert"]),
					ShaderFile::fromSource(ShaderType::Frag, sources["hdrScaleScene_frag"])
			}));
		}
	}

}
