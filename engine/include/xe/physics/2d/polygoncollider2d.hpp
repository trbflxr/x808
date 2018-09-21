//
// Created by FLXR on 9/18/2018.
//

#ifndef X808_POLYGONCOLLIDER2D_HPP
#define X808_POLYGONCOLLIDER2D_HPP


#include <xe/gfx/polygon.hpp>
#include <xe/physics/2d/collider2d.hpp>

class b2PolygonShape;

namespace xe {

	class XE_API PolygonCollider2D : public Collider2D {
	public:
		explicit PolygonCollider2D(PhysicsWorld2D *world, ColliderType type, Polygon *polygon);
		~PolygonCollider2D() override;

	protected:
		void update() override;

	private:
		b2PolygonShape *shape;
	};

}


#endif //X808_POLYGONCOLLIDER2D_HPP
