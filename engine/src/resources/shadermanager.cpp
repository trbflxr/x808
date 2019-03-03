//
// Created by FLXR on 7/22/2018.
//

#include <xetools/spak.hpp>
#include <xe/utils/logger.hpp>
#include <xe/gfx/context.hpp>
#include <xe/resources/shadermanager.hpp>

namespace xe {

	ShaderManager::ShaderManager() {
		sources = spak::unpackShaders("pack001.pak");

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
			XE_CORE_ERROR("[ShaderManager]: shader '", shader->getName(), "' already exist and be deleted");

			delete shader;
			return false;
		}

		instance().shaders.emplace(shader->getName(), shader);
		return true;
	}

	const Shader *ShaderManager::get(const string &name) {
		auto &&it = instance().shaders.find(name);
		if (it == instance().shaders.end()) {
			XE_CORE_FATAL("[ShaderManager]: shader '", name, "' not found!");

			return nullptr;
		}

		return it->second;
	}

	const string &ShaderManager::getSource(const string &name) {
		static string empty;

		auto &&it = instance().sources.find(name);
		if (it == instance().sources.end()) {
			XE_CORE_FATAL("[ShaderManager]: source '", name, "' not found!");
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

		shaders.emplace("dLightRenderer2D", new Shader("dLightRenderer2D", {
				ShaderFile::fromSource(ShaderType::Vert, sources["lightRenderer2D_vert"]),
				ShaderFile::fromSource(ShaderType::Frag, sources["lightRenderer2D_frag"])
		}));


		///----- render texture shaders -----///
		//render texture 2d
		shaders.emplace("dRenderTexture2D", new Shader("dRenderTexture2D", {
				ShaderFile::fromSource(ShaderType::Vert, sources["commonGeneric_vert"]),
				ShaderFile::fromSource(ShaderType::Frag, sources["renderTexture2D_frag"])
		}));

		///----- gbuffer shaders -----///
		//includes
		const std::vector<string> geomInclude{sources["1_camera_ubo"],
		                                      sources["gbufferFunctions_include"],
		                                      sources["linearDepth_include"]};


		shaders.emplace("dGeomShader", new Shader("dGeomShader", {
				ShaderFile::fromSource(ShaderType::Vert, sources["gbufferGeometry_vert"],
				                       {sources["1_camera_ubo"]}),
				ShaderFile::fromSource(ShaderType::Geom, sources["gbufferGeometry_geom"],
				                       {sources["1_camera_ubo"]}),
				ShaderFile::fromSource(ShaderType::Frag, sources["gbufferGeometry_frag"],
				                       {geomInclude})
		}));

		//gbuffer stencil shader
		shaders.emplace("dStencil", new Shader("dStencil", {
				ShaderFile::fromSource(ShaderType::Vert, sources["gbufferStencil_vert"],
				                       {sources["1_camera_ubo"]})
		}));


		//gbuffer light accumulation shader
		shaders.emplace("dAccumulation", new Shader("dAccumulation", {
				ShaderFile::fromSource(ShaderType::Vert, sources["commonGeneric_vert"]),
				ShaderFile::fromSource(ShaderType::Frag, sources["gbufferAccumulation_frag"])
		}));

		///----- final fx shader -----///
		shaders.emplace("dFinalFX", new Shader("dFinalFX", {
				ShaderFile::fromSource(ShaderType::Vert, sources["commonGeneric_vert"]),
				ShaderFile::fromSource(ShaderType::Frag, sources["final_frag"],
				                       {sources["fxaa_include"]})
		}));
	}

}
