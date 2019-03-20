//
// Created by FLXR on 3/20/2019.
//

#include <xe/gfx/ambientocclusion.hpp>

namespace xe {

	AmbientOcclusion::AmbientOcclusion(uint width, uint height, AOType type) :
			RenderEffect(width, height),
			type(type) {

		ssao = new SSAO(width, height);
		hbao = new HBAO(width, height);
	}

	AmbientOcclusion::~AmbientOcclusion() {
		delete ssao;
		delete hbao;
	}

	void AmbientOcclusion::calculateAO(const Texture *position, const Texture *normal, const Texture *depth,
	                                   const Camera *camera, const Quad *quad) {

		switch (type) {
			case AOType::Ssao: {
				ssao->calculateAO(normal, position, quad);
				break;
			}
			case AOType::Hbao: {
				hbao->calculateAO(normal, depth, camera, quad);
				break;
			}

			default: break;
		}
	}

	const Texture *AmbientOcclusion::getAO() const {
		switch (type) {
			case AOType::Ssao: return ssao->getAO();
			case AOType::Hbao: return hbao->getAO();
			default: return nullptr;
		}
	}

	const char *AmbientOcclusion::typeToString(AOType type) {
		switch (type) {
			case AOType::Ssao: return "SSAO";
			case AOType::Hbao: return "HBAO";
			default: return "None";
		}
	}

	AOType AmbientOcclusion::stringToType(const char *ao) {
		if (strcmp(ao, "SSAO") == 0) return AOType::Ssao;
		if (strcmp(ao, "HBAO") == 0) return AOType::Hbao;
		return AOType::None;
	}

}