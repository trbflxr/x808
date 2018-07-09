//
// Created by FLXR on 7/9/2018.
//

#include "mesh.hpp"

namespace xe { namespace gfx {

	Mesh::Mesh(api::VertexArray *vertexArray, api::IndexBuffer *indexBuffer, MaterialInstance *materialInstance) :
			vertexArray(vertexArray),
			indexBuffer(indexBuffer),
			materialInstance(materialInstance) { }

	Mesh::Mesh(const Mesh *other) :
			vertexArray(other->vertexArray),
			indexBuffer(other->indexBuffer),
			materialInstance(other->materialInstance) { }

	Mesh::~Mesh() {
		delete vertexArray;
		delete indexBuffer;
		delete materialInstance;
	}

	void Mesh::render(Renderer3D &renderer) {
		materialInstance->bind();

		vertexArray->bind();
		indexBuffer->bind();
		vertexArray->draw(indexBuffer->getCount());
		indexBuffer->unbind();
		vertexArray->unbind();

		materialInstance->unbind();
	}

}}