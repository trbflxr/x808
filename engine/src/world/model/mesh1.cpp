//
// Created by FLXR on 8/13/2018.
//

#include "mesh1.hpp"
#include "gfx/renderer.hpp"

namespace xe {

	Mesh1::Mesh1(const std::string_view &id) : id(id) { }

	Mesh1::Mesh1(const std::string_view &id, const IndexedModel &model, Material1 *material) :
			id(id),
			material(material) {

		initMesh(model);
	}

	Mesh1::~Mesh1() {
		delete vertexArray;
		delete indexBuffer;
	}

	void Mesh1::initMesh(const IndexedModel &model) {
		uint indicesSize = static_cast<uint>(model.indices.size());

		api::VertexBuffer *buffer = api::VertexBuffer::create(BufferUsage::StaticDraw);

		api::BufferLayout layout;
		layout.push<vec3>("POSITION");
		layout.push<vec3>("NORMAL");
		layout.push<vec3>("TANGENT");
		layout.push<vec2>("UV");
		buffer->setLayout(layout);

		size_t size = model.positions.size();
		Vertex *data = new Vertex[size];

		for (size_t i = 0; i < size; ++i) {
			data[i].position = model.positions[i];
			data[i].uv = model.uvs[i];
			data[i].normal = model.normals[i];
			data[i].tangent = model.tangents[i];
		}

		buffer->setData(static_cast<uint>(size * sizeof(Vertex)), data);
		delete[] data;

		vertexArray = api::VertexArray::create();
		vertexArray->pushBuffer(buffer);

		indexBuffer = api::IndexBuffer::create(&model.indices[0], indicesSize);
	}

	Mesh1 *Mesh1::spotLightMesh() {
		static Mesh1 m("SpotLight", IndexedModel::getConeModel(), nullptr);
		return &m;
	}

	Mesh1 *Mesh1::pointLightMesh() {
		static Mesh1 m("PointLight", IndexedModel::getIcosphereModel(), nullptr);
		return &m;
	}

}