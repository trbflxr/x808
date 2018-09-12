//
// Created by FLXR on 9/11/2018.
//

#include <Box2D/Box2D.h>
#include <xe/math/math.hpp>
#include <xe/physics/2d/physicsworld2d.hpp>
#include <xe/physics/2d/collider2d.hpp>

namespace xe {

	b2BodyType xeToBox2DBody(ColliderType type) {
		switch (type) {
			case ColliderType::Static: return b2_staticBody;
			case ColliderType::Dynamic: return b2_dynamicBody;
			case ColliderType::Kinematic: return b2_kinematicBody;
			default: return b2_staticBody;
		}
	}

	Collider2D::Collider2D(PhysicsWorld2D *world, ColliderType type, Transform2D *transform) :
			transform(transform),
			type(type) {

		b2BodyDef bodyDef;
		bodyDef.position = transform->getPosition();
		bodyDef.angle = to_rad(transform->getRotation());
		bodyDef.type = xeToBox2DBody(type);

		body = world->world->CreateBody(&bodyDef);
		body->SetUserData(this);
	}

	void Collider2D::update() {
		transform->setPosition(getPosition());
		transform->setRotation(getRotation());
	}

	void Collider2D::set(const vec2 &position, float angle) {
		body->SetTransform(position, to_rad(angle));
	}

	vec2 Collider2D::getPosition() const {
		return body->GetPosition();
	}

	float Collider2D::getRotation() const {
		return to_deg(body->GetAngle());
	}

	vec2 Collider2D::getLocalCenter() const {
		return body->GetLocalCenter();
	}

	vec2 Collider2D::setWorldCenter() const {
		return body->GetWorldCenter();
	}

	vec2 Collider2D::getLinearVelocity() const {
		return body->GetLinearVelocity();
	}

	void Collider2D::setLinearVelocity(const vec2 &v) {
		body->SetLinearVelocity(v);
	}

	float Collider2D::getAngularVelocity() const {
		return body->GetAngularVelocity();
	}

	void Collider2D::setAngularVelocity(float omega) {
		body->SetAngularVelocity(omega);
	}

	void Collider2D::applyForce(const vec2 &force, const vec2 &point, bool wake) {
		body->ApplyForce(force, point, wake);
	}

	void Collider2D::applyForceToCenter(const vec2 &force, bool wake) {
		body->ApplyForceToCenter(force, wake);
	}

	void Collider2D::applyTorque(float torque, bool wake) {
		body->ApplyTorque(torque, wake);
	}

	void Collider2D::applyLinearImpulse(const vec2 &impulse, const vec2 &point, bool wake) {
		body->ApplyLinearImpulse(impulse, point, wake);
	}

	void Collider2D::applyLinearImpulseToCenter(const vec2 &impulse, bool wake) {
		body->ApplyLinearImpulseToCenter(impulse, wake);
	}

	void Collider2D::applyAngularImpulse(float impulse, bool wake) {
		body->ApplyAngularImpulse(impulse, wake);
	}

	float Collider2D::getLinearDamping() const {
		return body->GetLinearDamping();
	}

	void Collider2D::setLinearDamping(float linearDamping) {
		body->SetLinearDamping(linearDamping);
	}

	float Collider2D::getAngularDamping() const {
		return body->GetAngularDamping();
	}

	void Collider2D::setAngularDamping(float angularDamping) {
		body->SetAngularDamping(angularDamping);
	}

	float Collider2D::getGravityScale() const {
		return body->GetGravityScale();
	}

	void Collider2D::setGravityScale(float scale) {
		body->SetGravityScale(scale);
	}

	void Collider2D::setSleepingAllowed(bool flag) {
		body->SetSleepingAllowed(flag);
	}

	bool Collider2D::isSleepingAllowed() const {
		return body->IsSleepingAllowed();
	}

	void Collider2D::setAwake(bool flag) {
		body->SetAwake(flag);
	}

	bool Collider2D::isAwake() const {
		return body->IsAwake();
	}

	void Collider2D::setActive(bool flag) {
		body->SetActive(flag);
	}

	bool Collider2D::isActive() const {
		return body->IsActive();
	}

	void Collider2D::setFixedRotation(bool flag) {
		body->SetFixedRotation(flag);
	}

	bool Collider2D::isFixedRotation() const {
		return body->IsFixedRotation();
	}

	float Collider2D::getFriction() const {
		return body->GetFixtureList()[0].GetFriction();
	}

	void Collider2D::setFriction(float friction) {
		body->GetFixtureList()[0].SetFriction(friction);
	}

	float Collider2D::getRestitution() const {
		return body->GetFixtureList()[0].GetRestitution();
	}

	void Collider2D::setRestitution(float restitution) {
		body->GetFixtureList()[0].SetRestitution(restitution);
	}

	float Collider2D::getDensity() const {
		return body->GetFixtureList()[0].GetDensity();
	}

	void Collider2D::setDensity(float density) {
		body->GetFixtureList()[0].SetDensity(density);
		body->ResetMassData();
	}

}