//
// Created by FLXR on 5/14/2019.
//

#ifndef X808_SENSOR2D_HPP
#define X808_SENSOR2D_HPP


#include <xe/gfx/2d/rectangleshape.hpp>

class b2PolygonShape;
struct b2FixtureDef;
class b2Body;

namespace xe {

	class PhysicsWorld2D;

	class XE_API Sensor2D {
	public:
		explicit Sensor2D(PhysicsWorld2D *world, RectangleShape *rect, const vec2 &center, float rotation = 0.0f);
		virtual ~Sensor2D();

		uint16 getCategoryBits() const;
		void setCategoryBits(uint16 bits);

		uint16 getMask() const;
		void setMask(uint16 bits);

		void setUserData(void *data);
		void *getUserData() const;

	protected:
		virtual void update();

	private:
		friend class Collider2D;

		PhysicsWorld2D *world;

		vec2 center;
		RectangleShape *rect;

		b2PolygonShape *shape;
		b2FixtureDef *fixtureDef;

		b2Filter filter;
		b2Fixture *fixture;
	};

}

#endif //X808_SENSOR2D_HPP
