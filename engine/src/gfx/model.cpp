//
// Created by FLXR on 7/10/2018.
//

#include "model.hpp"

namespace xe { namespace gfx {

	Model::Model(IndexedModel &model, MaterialInstance *materialInstance) {

		auto *buffer = api::VertexBuffer::create(api::BufferType::STATIC);

		uint size = static_cast<uint>(model.positions.size() + model.normals.size() + model.uvs.size());

		byte* data = new byte[size];
		memset(data, 0, size);

		memcpy(data, &model.positions[0], model.positions.size());
		memcpy(data + model.positions.size(), &model.normals[0], model.normals.size());
		memcpy(data + model.normals.size(), &model.uvs[0], model.uvs.size());

		buffer->setData(size, data);

		delete[] data;

		api::BufferLayout layout;
		layout.push<vec3>("POSITION");
		layout.push<vec3>("NORMAL");
		layout.push<vec2>("TEXCOORD");

		buffer->setLayout(layout);

		auto *vertexArray = api::VertexArray::create();
		vertexArray->pushBuffer(buffer);

		auto *ib = api::IndexBuffer::create(&model.indices[0], static_cast<uint>(model.indices.size()));

		mesh = new Mesh(vertexArray, ib, materialInstance);
	}

	Model::~Model() {
		delete mesh;
	}

	void Model::render(Renderer3D *renderer) {
		mesh->render(renderer);
	}

}}