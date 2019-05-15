//
// Created by FLXR on 3/1/2019.
//

#include <xe/gfx/mesh.hpp>
#include <xe/gfx/renderer.hpp>

namespace xe {

  Mesh::Mesh(const string &name, const IndexedModel &model) :
      name(name),
      vao(nullptr),
      ibo(nullptr) {

    init(model);
  }

  Mesh::Mesh(const string &name) :
      name(name),
      vao(nullptr),
      ibo(nullptr) { }

  Mesh::~Mesh() {
    delete ibo;
    delete vao;
  }

  void Mesh::init(const IndexedModel &model) {
    VertexBuffer *buffer = new VertexBuffer(BufferUsage::StaticDraw);

    BufferLayout layout;
    layout.push<vec3>("pos");
    layout.push<vec3>("normal");
    layout.push<vec3>("tangent");
    layout.push<vec2>("uv");
    buffer->setLayout(layout);

    const size_t size = model.positions.size();
    Vertex3D *data = new Vertex3D[size];

    for (size_t i = 0; i < size; ++i) {
      data[i].pos = model.positions[i];
      data[i].uv = model.uvs[i];
      data[i].normal = model.normals[i];
      data[i].tangent = model.tangents[i];
    }

    buffer->setData(static_cast<uint>(size * sizeof(Vertex3D)), data);
    delete[] data;

    vao = new VertexArray();
    vao->pushBuffer(buffer);

    const size_t indicesSize = model.indices.size();
    ibo = new IndexBuffer(&model.indices[0], indicesSize);
  }

  Mesh *Mesh::spotLightMesh(const string &name) {
    return new Mesh(name, IndexedModel::getConeModel());
  }

  Mesh *Mesh::pointLightMesh(const string &name) {
    return new Mesh(name, IndexedModel::getIcosphereModel());
  }

  void Mesh::render(BeginMode mode) const {
    vao->bind();
    ibo->bind();
    vao->drawElements(ibo->getCount(), mode);
    ibo->unbind();
    vao->unbind();

    Renderer::incDC();
  }

  void Mesh::renderInstanced(BeginMode mode, uint count) const {
    vao->bind();
    ibo->bind();
    vao->drawElementsInstanced(ibo->getCount(), mode, count);
    ibo->unbind();
    vao->unbind();

    Renderer::incDC();
  }

}