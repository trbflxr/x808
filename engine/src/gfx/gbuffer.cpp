//
// Created by FLXR on 3/2/2019.
//

#include <xe/gfx/gbuffer.hpp>
#include <xe/resources/shadermanager.hpp>
#include <xe/resources/texturemanager.hpp>
#include <xe/gfx/renderer.hpp>

namespace xe {


	GBuffer::GBuffer(uint width, uint height) :
			width(width),
			height(height),
			defaultNormal(GETTEXTURE("defaultNormal")),
			defaultSpecular(GETTEXTURE("defaultSpecular")) {

		createShaders();
		createTextures();

		buffer = new FrameBuffer("GBuffer");
		buffer->load({std::make_pair(Attachment::Depth, depth),
		              std::make_pair(Attachment::Color0, position),
		              std::make_pair(Attachment::Color1, normals),
		              std::make_pair(Attachment::Color2, albedo)});
	}

	GBuffer::~GBuffer() {
		delete depth;
		delete position;
		delete normals;
		delete albedo;

		delete buffer;
	}

	void GBuffer::createTextures() {
		static TextureParameters params(TextureTarget::Tex2D);
		params.internalFormat = PixelInternalFormat::DepthComponent16;
		params.format = PixelFormat::DepthComponent;
		params.pixelType = PixelType::Float;
		params.minFilter = TextureMinFilter::Nearest;
		params.magFilter = TextureMagFilter::Nearest;
		params.wrap = TextureWrap::Clamp;
		params.mipMapLevels = 0;
		params.anisotropy = 0;

		depth = new Texture("gBufferDepth", width, height, 0, params);

		params.format = PixelFormat::Rgb;
		params.internalFormat = PixelInternalFormat::Rgb16f;
		position = new Texture("gBufferPositions", width, height, 0, params);

		params.format = PixelFormat::Rgb;
		params.internalFormat = PixelInternalFormat::Rgb10A2;
		normals = new Texture("gBufferNormals", width, height, 0, params);

		params.internalFormat = PixelInternalFormat::Rgba;
		params.format = PixelFormat::Rgba;
		albedo = new Texture("gBufferAlbedo", width, height, 0, params);
	}

	void GBuffer::createShaders() {
		geometry = GETSHADER("dGBuffer");
		accumulation = GETSHADER("dAccumulation");

		geometry->bindUniformBlock("Camera", 1);
		accumulation->bindUniformBlock("Camera", 1);
	}

	void GBuffer::passGeometry(const std::vector<Model *> &models) const {
		static Attachment attachments[3] = {Attachment::Color0,
		                                    Attachment::Color1,
		                                    Attachment::Color2};

		buffer->bindDraw(attachments, 3);

		Renderer::clear(RendererBufferColor | RendererBufferDepth);
		Renderer::setViewport(0, 0, width, height);

		geometry->bind();

		for (const auto &m : models) {
			geometry->setUniform("model", &m->toMatrix(), sizeof(mat4));
			uint d = geometry->getSampler("sampler0");
			uint s = geometry->getSampler("sampler1");
			uint n = geometry->getSampler("sampler2");


			Material *mt = m->getMaterial();
			mt->diffuse->bind(d);

			if (mt->normal) {
				mt->normal->bind(n);
			} else {
				defaultNormal->bind(n);
			}

			if (mt->specular) {
				mt->specular->bind(s);
			} else {
				defaultSpecular->bind(s);
			}


			geometry->updateUniforms();


			m->render(BeginMode::Triangles);

			mt->diffuse->unbind(d);
			if (mt->normal) {
				mt->normal->unbind(n);
			} else {
				defaultNormal->unbind(n);
			}

			if (mt->specular) {
				mt->specular->unbind(s);
			} else {
				defaultSpecular->unbind(s);
			}
		}

		geometry->unbind();

		buffer->unbind();
	}

}
