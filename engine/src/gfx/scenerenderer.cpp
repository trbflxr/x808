//
// Created by FLXR on 8/17/2018.
//

#include <xe/gfx/scenerenderer.hpp>
#include <xe/gfx/defaultuniforms.hpp>
#include <xe/gfx/renderer.hpp>

namespace xe {

	void SceneRenderer::drawMeshes(BeginMode mode, const std::vector<UniqueMesh *> &meshes, Shader *shader,
	                               const mat4 &transform, float delta, bool useMaterial) {

		for (auto &&mesh : meshes) {
			const mat4 &model = mesh->transform.toMatrix();

			//world matrix
			shader->setUniform(uniform::model, &model, sizeof(mat4));

			//todo: check
//			tempMat = mat4::invert(tempMat);
//			tempMat = mat4::transpose(tempMat);

//			shader->setUniform(uniform::modelNormal, &tempMat, sizeof(mat4));

			//sampler slots
			int32 dfs = -1;
			int32 sps = -1;
			int32 nrs = -1;
			int32 dss = -1;
			int32 prs = -1;

			const Material *m = mesh->mesh->getMaterial();

			if (useMaterial) {
				//set mesh uniforms
				shader->setUniform(uniform::diffuseColor, &m->diffuseColor, sizeof(vec3));
				shader->setUniform(uniform::emission, &m->emission, sizeof(float));
				shader->setUniform(uniform::specularColor, &m->specularColor, sizeof(vec3));
				shader->setUniform(uniform::specularShininess, &m->specularShininess, sizeof(float));
				shader->setUniform(uniform::displacementStrength, &m->displacementStrength, sizeof(float));

				//textures
				dfs = setTexture(shader, m->diffuse, uniform::diffuseTexture, uniform::enableDiffuseTexture);
				sps = setTexture(shader, m->specular, uniform::specularTexture, uniform::enableSpecularTexture);
				nrs = setTexture(shader, m->normal, uniform::normalTexture, uniform::enableNormalTexture);
				dss = setTexture(shader, m->displacement, uniform::dispTexture, uniform::enableDispTexture);
				prs = setTexture(shader, m->parallax, uniform::parallaxTexture, uniform::enableParallaxTexture);
			}

			shader->updateUniforms();
			mesh->mesh->render(mode);

			if (dfs != -1) m->diffuse->unbind((uint) dfs);
			if (sps != -1) m->specular->unbind((uint) sps);
			if (nrs != -1) m->normal->unbind((uint) nrs);
			if (dss != -1) m->displacement->unbind((uint) dss);
			if (prs != -1) m->parallax->unbind((uint) prs);
		}
	}

	void SceneRenderer::drawLights(BeginMode mode, const std::vector<Light *> &lights,
	                               Shader *shader, const mat4 &transform, float delta, bool displayBounds) {

		for (auto &&light : lights) {
			if (!light->getMesh()) continue;

			//transform
			const mat4 model = light->transform.toMatrix();
			shader->setUniform(uniform::model, &model, sizeof(mat4));

			//todo: check
//			tempMat = mat4::invert(tempMat);
//			tempMat = mat4::transpose(tempMat);

//			shader->setUniform(uniform::modelNormal, &tempMat, sizeof(mat4));

			//values
			shader->setUniform(uniform::diffuseColor, &light->color, sizeof(vec3));
			shader->setUniform(uniform::emission, &light->objectEmission, sizeof(float));
			shader->setUniform(uniform::specularColor, &vec3::Zero, sizeof(vec3));
			shader->setUniform(uniform::specularShininess, &disabled, sizeof(float));
			shader->setUniform(uniform::displacementStrength, &disabled, sizeof(float));

			//disable textures
			shader->setUniform(uniform::enableDiffuseTexture, &disabled, sizeof(int32));
			shader->setUniform(uniform::enableSpecularTexture, &disabled, sizeof(int32));
			shader->setUniform(uniform::enableNormalTexture, &disabled, sizeof(int32));
			shader->setUniform(uniform::enableDispTexture, &disabled, sizeof(int32));
			shader->setUniform(uniform::enableParallaxTexture, &disabled, sizeof(int32));

			//set cull face for light object
			if (light->getType() == Light::Type::Spot) {
				Renderer::setCullFace(CullFace::Back);
			} else {
				Renderer::setCullFace(CullFace::Front);
			}

			//render
			shader->updateUniforms();
			light->getMesh()->render(mode);

			//display bounds
			if (displayBounds) {
				Renderer::enableCullFace(false);
				Renderer::setPolygonMode(MaterialFace::FrontAndBack, PolygonMode::Line);

				const mat4 &bModel = light->transform.toMatrix().clearScale() * light->getBoundsMatrix();
				shader->setUniform(uniform::model, &bModel, sizeof(mat4));
				shader->updateUniforms();

				light->getMesh()->render(mode);

				Renderer::setPolygonMode(MaterialFace::FrontAndBack, PolygonMode::Fill);
				Renderer::enableCullFace(true);
			}
		}

		Renderer::setCullFace(CullFace::Back);
	}

	void SceneRenderer::drawLightBounds(const Light *light, Shader *shader) {
		const mat4 &bModel = light->transform.toMatrix().clearScale() * light->getBoundsMatrix();

		shader->setUniform(uniform::model, &bModel, sizeof(mat4));

		shader->updateUniforms();

		light->getMesh()->render(BeginMode::Triangles);
	}

	int32 SceneRenderer::setTexture(Shader *shader, const Texture *texture, const char *sampler, const char *enable) {
		if (!texture) {
			shader->setUniform(enable, &disabled, sizeof(int32));
			return -1;
		}

		shader->setUniform(enable, &enabled, sizeof(int32));

		uint slot = shader->getSampler(sampler);
		texture->bind(slot);

		return slot;
	}

}