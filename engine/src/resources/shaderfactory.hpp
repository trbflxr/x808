//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_SHADERFACTORY_HPP
#define X808_SHADERFACTORY_HPP


#include "common.hpp"
#include "gfx/api/shader.hpp"

namespace xe { namespace gfx { namespace sf {

	//2d
	api::Shader XE_API *batchRendererShader();


	//3d forward
	api::Shader XE_API *basicForwardShader();
	api::Shader XE_API *forwardAmbientShader();
	api::Shader XE_API *forwardDirectionalShader();
	api::Shader XE_API *forwardPointShader();
	api::Shader XE_API *forwardSpotShader();

}}}


#endif //X808_SHADERFACTORY_HPP
