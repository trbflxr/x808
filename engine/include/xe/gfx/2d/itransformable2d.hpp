//
// Created by FLXR on 9/13/2018.
//

#ifndef X808_ITRANSFORMABLE2D_HPP
#define X808_ITRANSFORMABLE2D_HPP


#include <xe/math/transform2d.hpp>

namespace xe {

	class ITransformable2D {
	public:
		mutable Transform2D transform;
	};

}


#endif //X808_ITRANSFORMABLE2D_HPP
