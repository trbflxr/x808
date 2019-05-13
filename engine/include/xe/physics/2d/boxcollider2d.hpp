//
// Created by FLXR on 9/12/2018.
//

#ifndef X808_BOXCOLLIDER2D_HPP
#define X808_BOXCOLLIDER2D_HPP


#include <xe/gfx/2d/rectangleshape.hpp>
#include <xe/physics/2d/collider2d.hpp>

class b2PolygonShape;

namespace xe {

	class XE_API BoxCollider2D : public Collider2D {
	public:
		explicit BoxCollider2D(PhysicsWorld2D *world, ColliderType type,
		                       RectangleShape *rect, bool fixedRotation = false);
		~BoxCollider2D() override;

		void recreate() override;

	protected:
		void update() override;

	private:
		b2PolygonShape *shape;
	};

}

#endif //X808_BOXCOLLIDER2D_HPP
