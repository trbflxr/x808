//
// Created by FLXR on 8/7/2018.
//


#include <xe/gfx/fx/quad.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/shadermanager.hpp>

namespace xe { namespace fx {

	Quad::Quad(uint width, uint height) :
			RenderEffect(width, height) {

		//buffers
		vec3 positions[] = {{-1.0f, 1.0f,  0.0f},
		                    {1.0f,  1.0f,  0.0f},
		                    {1.0f,  -1.0f, 0.0f},
		                    {-1.0f, -1.0f, 0.0f}};

		uint indices[] = {0, 1, 2, 0, 2, 3};

		vao = new VertexArray();

		VertexBuffer *buffer = new VertexBuffer();
		BufferLayout layout;
		layout.push<vec3>("POSITION");

		buffer->setLayout(layout);
		buffer->setData(4 * sizeof(vec3), positions);

		vao->pushBuffer(buffer);

		ibo = new IndexBuffer(indices, 6);


		//texture shaders
		BaseShader *rt1 = new BaseShader("dRenderTexture1D", {
				ShaderFile::fromSource(ShaderType::Vert, ShaderManager::getSource("commonGeneric_vert")),
				ShaderFile::fromSource(ShaderType::Frag, ShaderManager::getSource("renderTexture1D_frag"))
		});
		ShaderManager::add(rt1);

		BaseShader *rt2 = new BaseShader("dRenderTexture2D", {
				ShaderFile::fromSource(ShaderType::Vert, ShaderManager::getSource("commonGeneric_vert")),
				ShaderFile::fromSource(ShaderType::Frag, ShaderManager::getSource("renderTexture2D_frag"))
		});
		ShaderManager::add(rt2);

		BaseShader *rt2a = new BaseShader("dRenderTexture2DArray", {
				ShaderFile::fromSource(ShaderType::Vert, ShaderManager::getSource("commonGeneric_vert")),
				ShaderFile::fromSource(ShaderType::Frag, ShaderManager::getSource("renderTexture2DArray_frag"))
		});
		ShaderManager::add(rt2a);

		BaseShader *rt3 = new BaseShader("dRenderTexture3D", {
				ShaderFile::fromSource(ShaderType::Vert, ShaderManager::getSource("commonGeneric_vert")),
				ShaderFile::fromSource(ShaderType::Frag, ShaderManager::getSource("renderTexture3D_frag"))
		});
		ShaderManager::add(rt3);

		BaseShader *rtc = new BaseShader("dRenderTextureCube", {
				ShaderFile::fromSource(ShaderType::Vert, ShaderManager::getSource("renderTextureCube_vert"),
				                       {ShaderManager::getSource("1_cameraSpatials_ubo")}),
				ShaderFile::fromSource(ShaderType::Frag, ShaderManager::getSource("renderTextureCube_frag"))
		});
		ShaderManager::add(rtc);

		BaseShader *rtca = new BaseShader("dRenderTextureCubeArray", {
				ShaderFile::fromSource(ShaderType::Vert, ShaderManager::getSource("renderTextureCube_vert"),
				                       {ShaderManager::getSource("1_cameraSpatials_ubo")}),
				ShaderFile::fromSource(ShaderType::Frag, ShaderManager::getSource("renderTextureCubeArray_frag"))
		});
		ShaderManager::add(rtca);


		renderTexture1D = new Shader(rt1);
		renderTexture2D = new Shader(rt2);
		renderTexture2DArray = new Shader(rt2a);
		renderTexture3D = new Shader(rt3);
		renderTextureCube = new Shader(rtc);
		renderTextureCubeArray = new Shader(rtca);
	}

	Quad::~Quad() {
		delete vao;
		delete ibo;

		delete renderTexture1D;
		delete renderTexture2D;
		delete renderTexture2DArray;
		delete renderTexture3D;
		delete renderTextureCube;
		delete renderTextureCubeArray;
	}

	void Quad::render() const {
		vao->bind();
		ibo->bind();

		vao->drawArrays(3, BeginMode::Triangles);

		ibo->unbind();
		vao->unbind();

		Renderer::incDC();
	}

	void Quad::renderBlend() const {
		Renderer::enableBlend(true);
		Renderer::setBlendEquation(BlendEquation::Add);
		Renderer::setBlendFunction(BlendFunction::One, BlendFunction::One);

		render();

		Renderer::enableBlend(false);
	}

	void Quad::renderFullQuad() const {
		vao->bind();
		ibo->bind();

		vao->drawArrays(6, BeginMode::Triangles);

		ibo->unbind();
		vao->unbind();

		Renderer::incDC();
	}

	void Quad::renderFullQuadBlend() const {
		Renderer::enableBlend(true);
		Renderer::setBlendEquation(BlendEquation::Add);
		Renderer::setBlendFunction(BlendFunction::One, BlendFunction::One);

		renderFullQuad();

		Renderer::enableBlend(false);
	}

	void Quad::render3D(uint depth) const {
		vao->bind();
		ibo->bind();

		vao->drawArraysInstanced(3, depth, BeginMode::Triangles);

		ibo->unbind();
		vao->unbind();

		Renderer::incDC();
	}

	void Quad::renderTexture(const Texture *texture, float size, int32 pos, int32 layer, int32 channel) {
		const float sizeX = width * size;
		const float sizeY = height * size;

		const float posX = width - sizeX;
		const float posY = sizeY * pos;

		const int32 l = static_cast<const int32>(math::clampf(layer, 0, texture->getDepth()));
		const int32 c = static_cast<const int32>(math::clampf(channel, -1, 3));

		Renderer::setViewport((uint) posX, (uint) posY, (uint) sizeX, (uint) sizeY);

		switch (texture->getTarget()) {
			case TextureTarget::Tex1D: {
				renderTexture(renderTexture1D, texture, 0, "", false);
				break;
			}

			case TextureTarget::Tex2D: {
				renderTexture(renderTexture2D, texture, c, "channel", false);
				break;
			}

			case TextureTarget::Tex3D: {
				renderTexture(renderTexture3D, texture, l, "layer", false);
				break;
			}

			case TextureTarget::Tex2DArray: {
				renderTexture(renderTexture2DArray, texture, l, "layer", false);
				break;
			}

			case TextureTarget::TexCubeMap: {
				renderTexture(renderTextureCube, texture, 0, "", true);
				break;
			}

			case TextureTarget::TexCubeMapArray: {
				renderTexture(renderTextureCubeArray, texture, l, "layer", true);
				break;
			}
		}
	}

	void Quad::renderTexture(Shader *shader, const Texture *texture, int32 data, const char *uniform, bool fullQuad) {
		shader->bind();

		if (strlen(uniform) > 0) {
			shader->setUniform(uniform, &data, sizeof(int32));
			shader->updateUniforms();
		}

		const uint slot = shader->getSampler("sampler0");

		texture->bind(slot);

		fullQuad ? renderFullQuad() : render();

		texture->unbind(slot);

		shader->unbind();
	}

}}
