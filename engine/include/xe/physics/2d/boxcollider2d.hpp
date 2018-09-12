//
// Created by FLXR on 9/12/2018.
//

#ifndef X808_BOXCOLLIDER2D_HPP
#define X808_BOXCOLLIDER2D_HPP


#include <xe/physics/2d/collider2d.hpp>

namespace xe {

	class XE_API BoxCollider2D : public Collider2D {
	public:
		explicit BoxCollider2D(PhysicsWorld2D *world, ColliderType type, Transform2D *transform);

	protected:
		void update() override;
	};

}

#endif //X808_BOXCOLLIDER2D_HPP
