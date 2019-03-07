//
// Created by FLXR on 9/6/2018.
//

#include <xe/gfx/2d/renderer2d.hpp>
#include <freetype-gl/freetype-gl.h>
#include <freetype-gl/utf8-utils.h>
#include <xe/gfx/renderer.hpp>
#include <xe/resources/shadermanager.hpp>

namespace xe {

#define R2D_VERTEX_SIZE     sizeof(VertexData)

#define R2D_SPRITE_SIZE     (R2D_VERTEX_SIZE * 4)
#define R2D_BUFFER_SIZE     (R2D_SPRITE_SIZE * XE_R2D_MAX_SPRITES)
#define R2D_INDICES_SIZE    (XE_R2D_MAX_SPRITES * 6)

	Renderer2D::Renderer2D(uint width, uint height, Camera *camera, uint maxLights) :
			width(width),
			height(height),
			camera(camera),
			shader(nullptr),
			indicesSize(0),
			indicesOffset(0),
			sampler0(0),
			activeTexture(nullptr),
			enableWireframe_(false),
			enableLighting(maxLights > 0),
			maxLights(0),
			ambient(0.1f),
			lightUBO(nullptr) {

		transformationStack.emplace_back(1.0f);
		transformationBack = &transformationStack.back();

		indices = new uint[R2D_INDICES_SIZE];
		indexBuffer = new IndexBuffer();

		if (enableLighting) {
			lightLayout.push<vec4>("position");
			lightLayout.push<vec4>("color");

			shader = GETSHADER("dLightRenderer2D");

			setMaxLights(maxLights);
		} else {
			shader = GETSHADER("dRenderer2D");
		}

		sampler0 = shader->getSampler("sampler0");

		setupBuffer();
	}

	Renderer2D::~Renderer2D() {
		delete indexBuffer;
		delete vertexArray;

		delete[] indices;
	}

	void Renderer2D::setMaxLights(uint lights) {
		XE_ASSERT(enableLighting, "You have to create renderer with lighting support for use it");
		if (!enableLighting || maxLights == lights) return;

		maxLights = lights;

		shader->setSourceConstant(ShaderType::Frag, "@MAX_PLIGHTS", std::to_string(maxLights));

		//set back ambient
		setAmbientLight(ambient);

		//create and bind uniform buffer
		delete lightUBO;
		lightUBO = new UniformBuffer(BufferStorage::Dynamic, 0, lightLayout, maxLights);

		shader->bindUniformBlock("Lights", 0);
	}

	void Renderer2D::setupBuffer() {
		VertexBuffer *buffer = new VertexBuffer(BufferUsage::DynamicDraw);
		buffer->resize(R2D_BUFFER_SIZE);

		BufferLayout layout;
		layout.push<vec3>("pos");
		layout.push<vec2>("uv");
		layout.push<byte>("color", 4, true);
		layout.push<int32>("useTexture");
		layout.push<int32>("text");

		buffer->setLayout(layout);

		vertexArray = new VertexArray();
		vertexArray->pushBuffer(buffer);
	}

	void Renderer2D::push(const mat4 &matrix, bool override) {
		transformationStack.push_back(override ? matrix : transformationStack.back() * matrix);
		transformationBack = &transformationStack.back();
	}

	void Renderer2D::pop() {
		if (transformationStack.size() > 1) {
			transformationStack.pop_back();
		}
		transformationBack = &transformationStack.back();
	}

	void Renderer2D::updateCamera() {
		shader->setUniform("projection", camera->getProjection().elements, sizeof(mat4));
		shader->setUniform("view", camera->getView().elements, sizeof(mat4));
	}

	void Renderer2D::updateIndexBuffer() {
		indexBuffer->setData(indices, indicesSize);
	}

	void Renderer2D::releaseBuffer() {
		vertexArray->getBuffer(0)->releasePointer();
		vertexArray->unbind();
	}

	int32 Renderer2D::submitTexture(const Texture *texture) {
		if (!activeTexture && texture) {
			activeTexture = texture;
			return 1;
		}

		if (!texture && activeTexture) {
			return 0;
		}

		if (activeTexture && texture) {
			if (activeTexture != texture) {
				releaseBuffer();
				flush();
				begin();

				activeTexture = texture;
				return 1;
			}
		}
		return 1;
	}

	void Renderer2D::appendIndices(const uint *indices, uint size, uint offset) {
		if (indicesSize + size >= R2D_INDICES_SIZE) {
			releaseBuffer();
			flush();
			beginInternal();
		}

		for (uint i = 0; i < size; ++i) {
			Renderer2D::indices[i + indicesSize] = indices[i] + indicesOffset;
		}

		indicesSize += size;
		indicesOffset += offset;
	}

	void Renderer2D::useLight(const Light2D *light) {
		XE_ASSERT(enableLighting, "You have to create renderer with lighting support for use it");
		if (lights.size() + 1 > maxLights) {
			XE_CORE_ERROR("Maximum 2d lights reached (", maxLights, ")");
			return;
		}

		lights.push_back(light);
	}

	void Renderer2D::setAmbientLight(const vec3 &color) {
		XE_ASSERT(enableLighting, "You have to create renderer with lighting support for use it");
		ambient = color;

		shader->setUniform("ambient", &ambient, sizeof(vec3));
	}

	void Renderer2D::begin() {
		Renderer::enableDepthTesting(false);
		Renderer::enableBlend(true);
		Renderer::setBlendFunction(BlendFunction::SourceAlpha, BlendFunction::OneMinusSourceAlpha);
		Renderer::setViewport(0, 0, width, height);

		updateCamera();

		if (enableLighting) {
			if (!lights.empty()) {
				int32 size = static_cast<int32>(lights.size());

				shader->setUniform("lightsSize", &size, sizeof(int32));
			}

			for (uint i = 0; i < lights.size(); ++i) {
				vec4 lightPos = vec4(lights[i]->getPosition().x, lights[i]->getPosition().y, 0.0f, 0.0f);
				vec4 lightColor = vec4(lights[i]->getColor(), lights[i]->getIntensity());

				lightUBO->bind();
				lightUBO->update(&lightPos, 0, i);
				lightUBO->update(&lightColor, 1, i);
				lightUBO->unbind();
			}

			lights.clear();
		}

		beginInternal();
	}

	void Renderer2D::beginInternal() {
		vertexArray->bind();
		buffer = static_cast<VertexData *>(vertexArray->getBuffer(0)->getPointer());
	}

	void Renderer2D::end() {
		releaseBuffer();
	}

	void Renderer2D::flush() {
		updateIndexBuffer();

		shader->bind();
		shader->updateUniforms();

		if (activeTexture) {
			activeTexture->bind(sampler0);
		}

		vertexArray->bind();
		indexBuffer->bind();

		if (enableWireframe_) {
			Renderer::setPolygonMode(MaterialFace::FrontAndBack, PolygonMode::Line);
		}

		vertexArray->drawElements(indicesSize, BeginMode::Triangles);

		if (enableWireframe_) {
			Renderer::setPolygonMode(MaterialFace::FrontAndBack, PolygonMode::Fill);
		}

		indexBuffer->unbind();
		vertexArray->unbind();

		if (activeTexture) {
			activeTexture->unbind(sampler0);
		}

		shader->unbind();

		indicesSize = 0;
		indicesOffset = 0;

		//increment draw calls
		Renderer::incDC();
	}

	void Renderer2D::submit(const IRenderable2D *target) {
		if (!target->isVisible()) return;

		const uint count = target->getPointCount();
		const uint indicesCount = target->getIndicesCount();

		if (count < 3) return;

		const Vertex2D *vertices = target->getVertices();
		const uint color = target->getColor();
		const Texture *texture = target->getTexture();

		const mat4 transform = *transformationBack * target->getTransformation();

		const int32 useTexture = submitTexture(texture);

		appendIndices(target->getIndices(), indicesCount, count);

		for (uint i = 0; i < count; ++i) {
			buffer->vertex = mat4::translateXY(transform, vertices[i].pos);

			//todo: refactor
			if (texture && texture->isFlipped()) {
				buffer->uv = vertices[count - i - 1].uv;
			} else {
				buffer->uv = vertices[i].uv;
			}

			buffer->color = color;
			buffer->useTexture = useTexture;
			buffer->text = 0;
			buffer++;
		}
	}

	void Renderer2D::submit(const Text *text) {
		const Font *font = text->getFont();
		const Texture *atlas = font->getTexture();
		submitTexture(atlas);

		const string &string = text->getString();
		const uint color = text->getTextColor();
		const uint outlineColor = text->getOutlineColor();
		const float scale = text->getFontScale();
		const float outlineThickness = text->getOutlineThickness();

		//transform
		const mat4 transform = *transformationBack * text->toMatrix();

		float x = 0.0f;
		float y = 0.0f;

		if (outlineThickness > 0.001f) {
			font->setRenderMode(Font::RenderMode::OutlineEdge);
			font->setOutlineThickness(outlineThickness);

			submitString(string, font, outlineColor, scale, transform, x, y);

			x = 0.0f;
		}

		font->setRenderMode(Font::RenderMode::Normal);
		font->setOutlineThickness(0.0f);

		submitString(string, font, color, scale, transform, x, y);
	}

	void Renderer2D::submitString(const string &str, const Font *font, uint color,
	                              float scale, const mat4 &transform, float &x, float &y) {

		static constexpr uint textIndicesSize = 6;
		static constexpr uint textIndices[textIndicesSize] = {0, 1, 2, 2, 3, 0};

		for (uint i = 0; i < str.length(); i++) {
			const ftgl::texture_glyph_t *glyph = static_cast<ftgl::texture_glyph_t *>(font->getGlyph(&str[i]));

			if (!glyph) continue;

			if (i > 0) {
				const float kerning = font->getKerning((void *) glyph, &str[i - 1]);
				x += kerning * scale;
			}

			float x0 = x + glyph->offset_x * scale;
			float y0 = y - glyph->offset_y * scale;
			float x1 = x0 + glyph->width * scale;
			float y1 = y0 + glyph->height * scale;

			float u0 = glyph->s0;
			float v0 = glyph->t0;
			float u1 = glyph->s1;
			float v1 = glyph->t1;

			appendIndices(textIndices, textIndicesSize, 4);

			buffer->vertex = mat4::translateXY(transform, x0, -y0);
			buffer->uv.x = u0;
			buffer->uv.y = v0;
			buffer->color = color;
			buffer->useTexture = 1;
			buffer->text = 1;
			++buffer;

			buffer->vertex = mat4::translateXY(transform, x0, -y1);
			buffer->uv.x = u0;
			buffer->uv.y = v1;
			buffer->useTexture = 1;
			buffer->text = 1;
			buffer->color = color;
			++buffer;

			buffer->vertex = mat4::translateXY(transform, x1, -y1);
			buffer->uv.x = u1;
			buffer->uv.y = v1;
			buffer->color = color;
			buffer->useTexture = 1;
			buffer->text = 1;
			++buffer;

			buffer->vertex = mat4::translateXY(transform, x1, -y0);
			buffer->uv.x = u1;
			buffer->uv.y = v0;
			buffer->color = color;
			buffer->useTexture = 1;
			buffer->text = 1;
			++buffer;

			x += glyph->advance_x * scale;
		}
	}

}
