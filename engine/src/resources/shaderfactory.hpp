//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_SHADERFACTORY_HPP
#define X808_SHADERFACTORY_HPP


#include "common.hpp"
#include "gfx/api/shader.hpp"

namespace xe { namespace gfx { namespace sf {

	XE_API api::Shader *batchRendererShader();

	XE_API api::Shader *basicForwardShader();

}}}


#endif //X808_SHADERFACTORY_HPP
