//
// Created by FLXR on 7/12/2018.
//

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.hpp"
#include "renderer.hpp"

namespace xe {

	Mesh::Mesh(const IndexedModel &model) {
		initMesh(model);
	}

	Mesh::Mesh(const std::string_view &path) {
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(path.data(), aiProcess_JoinIdenticalVertices |
		                                                      aiProcess_Triangulate |
		                                                      aiProcess_GenSmoothNormals |
		                                                      aiProcess_CalcTangentSpace |
		                                                      aiProcess_FlipUVs);
		if (!scene) {
			XE_FATAL("[Mesh]: unable to load model '", path, "'");
			XE_ASSERT(false);
			return;
		}
		IndexedModel model(scene->mMeshes[0]);

		initMesh(model);
	}

	Mesh::~Mesh() {
		delete vertexArray;
		delete indexBuffer;
	}

	void Mesh::initMesh(const IndexedModel &model) {
		indicesSize = static_cast<uint>(model.indices.size());

		api::VertexBuffer *buffer = api::VertexBuffer::create(api::VertexBuffer::Type::STATIC);

		api::BufferLayout layout;
		layout.push<vec3>("POSITION"); // Position
		layout.push<vec2>("TEXCOORD"); // UV
		layout.push<vec3>("NORMAL");   // Normal
		layout.push<vec3>("TANGENT");  // Tangent
		buffer->setLayout(layout);

		size_t size = model.positions.size();
		MeshVertexData *data = new MeshVertexData[size];

		for (size_t i = 0; i < size; ++i) {
			data[i].position = model.positions[i];
			data[i].uv = model.uvs[i];
			data[i].normal = model.normals[i];
			data[i].tangent = model.tangents[i];
		}

		buffer->setData(static_cast<uint>(size * sizeof(MeshVertexData)), data);
		delete[] data;

		vertexArray = api::VertexArray::create();
		vertexArray->pushBuffer(buffer);

		indexBuffer = api::IndexBuffer::create(&model.indices[0], indicesSize);
	}

	void Mesh::render() const {
		vertexArray->bind();
		indexBuffer->bind();

		vertexArray->drawElements(indicesSize);

		indexBuffer->unbind();
		vertexArray->unbind();

		Renderer::incDC();
	}

}