//
// Created by FLXR on 7/12/2018.
//

#include "forwardrenderer.hpp"

#include "resources/shaderfactory.hpp"
#include "resources/texturemanager.hpp"
#include "gfx/lights/ambientlight.hpp"
#include "renderer.hpp"

namespace xe { namespace gfx {

	ForwardRenderer::ForwardRenderer() {
		Renderer::enableCullFace(true);
		Renderer::enableDepthTesting(true);
		Renderer::enableDepthClamp(true);

		Renderer::setCullFace(CullFace::BACK);


		//temp
		lights.push_back(new AmbientLight(sf::forwardAmbientShader(), {0.3f, 0.3f, 0.3f}));


		//temp
		mat4 projection = math::translate({0.0f, 0.0f, 10.0f});
		mat4 view(1.0f);

		//temp
		//same order like in shader
		lights[0]->setUniform(0, &projection.elements, sizeof(mat4));
		lights[0]->setUniform(1, &view.elements, sizeof(mat4));

		//temp
		texture = &GETTEXTURE("rock");
	}

	ForwardRenderer::~ForwardRenderer() {

	}

	void ForwardRenderer::render(const Mesh *mesh) {
		Renderer::enableBlend(true);
		Renderer::setBlendFunction(BlendFunction::ONE, BlendFunction::ONE);
		Renderer::enableDepthMask(false);
		Renderer::setDepthFunction(DepthFunction::EQUAL);


		for (auto &&light : lights) {
			light->bindAndSetUniforms();

			texture->bind(0);
			mesh->render();
			texture->unbind(0);
		}

		Renderer::enableDepthMask(true);
		Renderer::enableBlend(false);
		Renderer::setDepthFunction(DepthFunction::LESS);
	}

}}