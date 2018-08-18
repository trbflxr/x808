//
// Created by FLXR on 7/22/2018.
//

#include <xetools/spak.hpp>
#include <xe/utils/log.hpp>
#include <xe/resources/shadermanager.hpp>

namespace xe {

	ShaderManager::ShaderManager() {
		sources = spak::unpack("pack001.pak");

		auto node = sources.extract("renderTexture2D_vert");
		node.key() = "commonGeneric_vert";
		sources.insert(std::move(node));

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

	const string &ShaderManager::getSource(const string &name) {
		static string empty;

		auto &&it = instance().sources.find(name);
		if (it == instance().sources.end()) {
			XE_FATAL("Source '", name, "' not found!");
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
		//2d renderer
		shaders.emplace("dBatchRenderer", new BaseShader("dBatchRenderer", {
				ShaderFile::fromSource(ShaderType::Vert, sources["batchRenderer_vert"], { }),
				ShaderFile::fromSource(ShaderType::Frag, sources["batchRenderer_frag"], { })
		}));

		//textures
		shaders.emplace("dRenderTexture1D", new BaseShader("dRenderTexture1D", {
				ShaderFile::fromSource(ShaderType::Vert, sources["commonGeneric_vert"], { }),
				ShaderFile::fromSource(ShaderType::Frag, sources["renderTexture1D_frag"], { })
		}));

		shaders.emplace("dRenderTexture2D", new BaseShader("dRenderTexture2D", {
				ShaderFile::fromSource(ShaderType::Vert, sources["commonGeneric_vert"], { }),
				ShaderFile::fromSource(ShaderType::Frag, sources["renderTexture2D_frag"], { })
		}));

		shaders.emplace("dRenderTexture2DArray", new BaseShader("dRenderTexture2DArray", {
				ShaderFile::fromSource(ShaderType::Vert, sources["commonGeneric_vert"], { }),
				ShaderFile::fromSource(ShaderType::Frag, sources["renderTexture2DArray_frag"], { })
		}));

		shaders.emplace("dRenderTexture3D", new BaseShader("dRenderTexture3D", {
				ShaderFile::fromSource(ShaderType::Vert, sources["commonGeneric_vert"], { }),
				ShaderFile::fromSource(ShaderType::Frag, sources["renderTexture3D_frag"], { })
		}));

		shaders.emplace("dRenderTextureCube", new BaseShader("dRenderTextureCube", {
				ShaderFile::fromSource(ShaderType::Vert, sources["renderTextureCube_vert"],
				                       {sources["1_cameraSpatials_ubo"]}),
				ShaderFile::fromSource(ShaderType::Frag, sources["renderTextureCube_frag"], { })
		}));

		shaders.emplace("dRenderTextureCubeArray", new BaseShader("dRenderTextureCubeArray", {
				ShaderFile::fromSource(ShaderType::Vert, sources["renderTextureCube_vert"],
				                       {sources["1_cameraSpatials_ubo"]}),
				ShaderFile::fromSource(ShaderType::Frag, sources["renderTextureCubeArray_frag"], { })
		}));

		//fx final
		shaders.emplace("dFinalFX", new BaseShader("dFinalFX", {
				ShaderFile::fromSource(ShaderType::Vert, sources["commonGeneric_vert"], { }),
				ShaderFile::fromSource(ShaderType::Frag, sources["finalScene_frag"], {sources["fxaa_include"]})
		}));

	}


}
