//
// Created by FLXR on 7/22/2018.
//

#ifndef X808_GLSHADERSOURCE_HPP
#define X808_GLSHADERSOURCE_HPP


namespace xe {	namespace internal {

		//batch renderer
		static const char *brVertGL =
		#include "shaders/batchRenderer.vert"
				;

		static const char *brFragGL =
		#include "shaders/batchRenderer.frag"
				;

}}


#endif //X808_GLSHADERSOURCE_HPP
