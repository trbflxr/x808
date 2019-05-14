//
// Created by FLXR on 9/11/2018.
//

#ifndef X808_COLLIDER2D_HPP
#define X808_COLLIDER2D_HPP


#include <xe/common.hpp>
#include <xe/math/vec2.hpp>
#include <xe/math/itransformable2d.hpp>

class b2Body;
struct b2BodyDef;
struct b2FixtureDef;

namespace xe {

	class PhysicsWorld2D;

	enum class ColliderType {
		Static,
		Dynamic,
		Kinematic
	};

	class XE_API Collider2D {
	public:
		virtual ~Collider2D();

		inline ColliderType getType() const { return type; }

		void set(const vec2 &position, float angle);

		virtual void recreate() = 0;

		uint16 getCategoryBits() const;
		void setCategoryBits(uint16 bits);

		uint16 getMask() const;
		void setMask(uint16 bits);

		vec2 getPosition() const;
		float getRotation() const;

		vec2 getLocalCenter() const;
		vec2 setWorldCenter() const;

		vec2 getLinearVelocity() const;
		void setLinearVelocity(const vec2 &v);

		float getAngularVelocity() const;
		void setAngularVelocity(float omega);

		void applyForce(const vec2 &force, const vec2 &point, bool wake);
		void applyForceToCenter(const vec2 &force, bool wake);

		void applyTorque(float torque, bool wake);

		void applyLinearImpulse(const vec2 &impulse, const vec2 &point, bool wake);
		void applyLinearImpulseToCenter(const vec2 &impulse, bool wake);

		void applyAngularImpulse(float impulse, bool wake);

		float getLinearDamping() const;
		void setLinearDamping(float linearDamping);

		float getAngularDamping() const;
		void setAngularDamping(float angularDamping);

		float getGravityScale() const;
		void setGravityScale(float scale);

		void setSleepingAllowed(bool flag);
		bool isSleepingAllowed() const;

		void setAwake(bool flag);
		bool isAwake() const;

		void setActive(bool flag);
		bool isActive() const;

		void setFixedRotation(bool flag);
		bool isFixedRotation() const;

		float getFriction() const;
		void setFriction(float friction);

		float getRestitution() const;
		void setRestitution(float restitution);

		float getDensity() const;
		void setDensity(float density);

		void setUserData(void *data);
		void *getUserData() const;

	protected:
		explicit Collider2D(PhysicsWorld2D *world, ColliderType type,
		                    ITransformable2D *transformable, bool fixedRotation);

		virtual void update();

		void create(PhysicsWorld2D *world);

	protected:
		friend class PhysicsWorld2D;

		PhysicsWorld2D *world;
		ITransformable2D *transformable;
		ColliderType type;
		b2BodyDef *bodyDef;
		b2FixtureDef *fixtureDef;
		b2Body *body;
	};

}


#endif //X808_COLLIDER2D_HPP
