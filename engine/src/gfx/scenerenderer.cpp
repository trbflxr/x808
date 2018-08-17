//
// Created by FLXR on 8/17/2018.
//

#include <xe/gfx/scenerenderer.hpp>
#include <xe/gfx/defaultuniforms.hpp>
#include <xe/gfx/renderer.hpp>

namespace xe {

	//0 - basic
	//1 - 0 + materials
	//2 - 1 + prev model matrix
	void SceneRenderer::drawMeshes(BeginMode mode, const std::vector<UniqueMesh *> &meshes, Shader *shader,
	                               const mat4 &transform, float delta, uint drawMode) {

		for (auto &&mesh : meshes) {
			mat4 tempMat = mesh->transformation;
			mat4 tempMatPrev = mesh->prevTransformation;

			//world matrix
			shader->setUniform(uniform::model, &tempMat, sizeof(mat4));

			//prev world matrix
			shader->setUniform(uniform::modelPrevious, &tempMatPrev, sizeof(mat4));
			if (drawMode > 1) mesh->prevTransformation = tempMat;

			tempMat = mat4::invert(tempMat);
			tempMat = mat4::transpose(tempMat);

			//model normal
			shader->setUniform(uniform::modelNormal, &tempMat, sizeof(mat4));

			//sampler slots
			int32 dfs = -1;
			int32 sps = -1;
			int32 nrs = -1;
			int32 dss = -1;
			int32 prs = -1;

			const Material *m = mesh->mesh->getMaterial();

			if (drawMode > 0) {
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

			mesh->mesh->render(mode);

			if (dfs > -1) m->diffuse->unbind((uint) dfs);
			if (sps > -1) m->specular->unbind((uint) sps);
			if (nrs > -1) m->normal->unbind((uint) nrs);
			if (dss > -1) m->displacement->unbind((uint) dss);
			if (prs > -1) m->parallax->unbind((uint) prs);
		}
	}

	void SceneRenderer::drawLights(BeginMode mode, const std::vector<Light *> &lights,
	                               Shader *shader, const mat4 &transform, float delta, bool displayBounds) {

		for (auto &&light : lights) {
			if (!light->getMesh()) continue;

			//transform
			mat4 tempMat = light->getMesh()->transformation;
			mat4 tempMatPrev = light->getMesh()->prevTransformation;

			shader->setUniform(uniform::model, &tempMat, sizeof(mat4));
			shader->setUniform(uniform::modelPrevious, &tempMatPrev, sizeof(mat4));

			light->getMesh()->prevTransformation = tempMat;

			//normals
			tempMat = mat4::invert(tempMat);
			tempMat = mat4::transpose(tempMat);

			shader->setUniform(uniform::modelNormal, &tempMat, sizeof(mat4));

			//values
			float dummy = 0.0f;

			shader->setUniform(uniform::diffuseColor, &light->color, sizeof(vec3));
			shader->setUniform(uniform::emission, &light->objectEmission, sizeof(float));
			shader->setUniform(uniform::specularColor, &vec3::Zero, sizeof(vec3));
			shader->setUniform(uniform::specularShininess, &dummy, sizeof(float));
			shader->setUniform(uniform::displacementStrength, &dummy, sizeof(float));

			//render
			light->getMesh()->mesh->render(mode);

			//display bounds
			if (displayBounds) {
				Renderer::enableCullFace(false);
				Renderer::setPolygonMode(MaterialFace::FrontAndBack, PolygonMode::Line);

				tempMat = light->getBoundingMesh()->transformation;
				shader->setUniform(uniform::model, &tempMat, sizeof(mat4));

				light->getBoundingMesh()->mesh->render(mode);

				Renderer::setPolygonMode(MaterialFace::FrontAndBack, PolygonMode::Fill);
				Renderer::enableCullFace(true);
			}
		}
	}

	void SceneRenderer::drawLightBounds(const Light *light, Shader *shader) {
		mat4 tempMat = light->getBoundingMesh()->transformation;
		shader->setUniform(uniform::model, &tempMat, sizeof(mat4));

		light->getBoundingMesh()->mesh->render(BeginMode::Triangles);
	}

	int32 SceneRenderer::setTexture(Shader *shader, const Texture *texture,
	                                const char *sampler, const char *enable) {

		if (!texture) return -1;

		int32 val = 1;
		shader->setUniform(enable, &val, sizeof(int32));

		uint slot = shader->getSampler(sampler);
		texture->bind(slot);

		return slot;
	}

}