//
// Created by FLXR on 9/18/2018.
//

#ifndef X808_CIRCLECOLLIDER2D_HPP
#define X808_CIRCLECOLLIDER2D_HPP


#include <xe/gfx/2d/circleshape.hpp>
#include <xe/physics/2d/collider2d.hpp>

class b2CircleShape;

namespace xe {

	class XE_API CircleCollider2D : public Collider2D {
	public:
		explicit CircleCollider2D(PhysicsWorld2D *world, ColliderType type, CircleShape *circle);
		~CircleCollider2D() override;

		void recreate() override;

	protected:
		void update() override;

	private:
		b2CircleShape *shape;
	};

}

#endif //X808_CIRCLECOLLIDER2D_HPP
