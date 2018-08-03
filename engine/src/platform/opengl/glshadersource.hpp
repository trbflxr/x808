//
// Created by FLXR on 7/22/2018.
//

#ifndef X808_GLSHADERSOURCE_HPP
#define X808_GLSHADERSOURCE_HPP


#include <string>

namespace xe { namespace gfx {

	std::string batchRendererShaderSourceGL();
	std::string forwardAmbientShaderSourceGL();
	std::string forwardDirectionalShaderSourceGL();
	std::string forwardPointShaderSourceGL();
	std::string forwardSpotShaderSourceGL();
	std::string shadowMapSourceGL();
	std::string filterNULLSourceGL();
	std::string filterGaussBlurSourceGL();
	std::string filterFXAASourceGL();

}}


#endif //X808_GLSHADERSOURCE_HPP
