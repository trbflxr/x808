//
// Created by FLXR on 9/11/2018.
//

#ifndef X808_PHYSICSWORLD2D_HPP
#define X808_PHYSICSWORLD2D_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/math/vec2.hpp>

class b2World;
class b2Body;

namespace xe {

	class XE_API PhysicsWorld2D {
	public:
		explicit PhysicsWorld2D(const vec2 &gravity);
		~PhysicsWorld2D();

		void update(float timeStep, uint velocityIterations, uint positionIterations);

	private:
		friend class Collider2D;

		b2World *world;
	};

}


#endif //X808_PHYSICSWORLD2D_HPP
