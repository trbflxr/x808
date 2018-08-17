//
// Created by FLXR on 8/13/2018.
//

#include <xe/world/model/mesh.hpp>

namespace xe {

	Mesh::Mesh(const string &id) :
			id(id),
			indexBuffer(nullptr),
			vertexArray(nullptr) { }

	Mesh::Mesh(const string &id, const IndexedModel &model, Material *material) :
			id(id),
			material(material),
			indexBuffer(nullptr),
			vertexArray(nullptr) {

		initMesh(model);
	}

	Mesh::~Mesh() {
		delete indexBuffer;
		delete vertexArray;
	}

	void Mesh::initMesh(const IndexedModel &model) {
		uint indicesSize = static_cast<uint>(model.indices.size());

		VertexBuffer *buffer = new VertexBuffer(BufferUsage::StaticDraw);

		BufferLayout layout;
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

		vertexArray = new VertexArray;
		vertexArray->pushBuffer(buffer);

		indexBuffer = new IndexBuffer(&model.indices[0], indicesSize);
	}

	Mesh *Mesh::spotLightMesh() {
		return new Mesh("SpotLight", IndexedModel::getConeModel(), nullptr);
	}

	Mesh *Mesh::pointLightMesh() {
		return new Mesh("PointLight", IndexedModel::getIcosphereModel(), nullptr);
	}

}