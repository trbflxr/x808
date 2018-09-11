//
// Created by FLXR on 9/11/2018.
//

#ifndef X808_COLLIDER2D_HPP
#define X808_COLLIDER2D_HPP


#include <xe/common.hpp>
#include <xe/math/vec2.hpp>
#include <xe/math/transform2d.hpp>

class b2Body;

namespace xe {

	class PhysicsWorld2D;

	enum class ColliderType {
		Static,
		Dynamic,
		Kinematic
	};

	class XE_API Collider2D {
	public:
		virtual ~Collider2D() = default;

		vec2 getPosition() const;
		float getRotation() const;

	protected:
		explicit Collider2D(PhysicsWorld2D *world, ColliderType type, Transform2D &transform);

	protected:
		ColliderType type;
		b2Body *body;
	};

}


#endif //X808_COLLIDER2D_HPP
