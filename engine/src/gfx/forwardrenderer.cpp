//
// Created by FLXR on 7/12/2018.
//

#include "forwardrenderer.hpp"

#include "math/transform.hpp"
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
		camera = new FPSCamera(math::perspective(80.0f, 8.0f / 6.0f, 0.1f, 1000));

		//temp
		texture = &GETTEXTURE("rock");
	}

	ForwardRenderer::~ForwardRenderer() {
		delete camera;
	}

	void ForwardRenderer::render(const Mesh *mesh) {
		if (Input::isKeyPressed(XE_KEY_S)) {
			camera->move({0, 0, 0.2f});
		}
		if (Input::isKeyPressed(XE_KEY_W)) {
			camera->move({0, 0, -0.2f});
		}
		if (Input::isKeyPressed(XE_KEY_D)) {
			camera->move({0.2f, 0, 0});
		}
		if (Input::isKeyPressed(XE_KEY_A)) {
			camera->move({-0.2f, 0, 0});
		}

		camera->update();


		//temp
		Transform transform;
		transform.setTranslation({0.0f, 0.0f, 10.0f});

		mat4 mvp = transform.toMatrix() * camera->getProjectionMatrix() * camera->getViewMatrix();

		//temp
		//same order like in shader
		lights[0]->setUniform("sys_MVP", &mvp.elements, sizeof(mat4), api::ShaderType::VERT);


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