#pragma once
#include "Collider.hpp"

namespace hv {
	enum class BodyType { Static = 0, Kinematic, Dynamic };

	class RigidBody {
	public:

		RigidBody();

		RigidBody(const RigidBody& other);

		RigidBody(sf::Vector2f pos, BodyType type);

		RigidBody(sf::Vector2f pos, BodyType type, const Collider& collider);

		~RigidBody();

		RigidBody* operator=(const RigidBody& other);

		// Modifiers
		void SetCollider(const Collider& collider);
		void SetPosition(sf::Vector2f position);
		void SetType(BodyType type);
		void SetGravityScale(float scale);
		void SetFixedRotation(bool fixed);
		void SetLinearDrag(float drag);
		void SetLinearVelocity(sf::Vector2f velocity);
		void AddForce(sf::Vector2f velocity);
		void SetRotation(float angle);

		// Accessors
		sf::Vector2f GetPosition() const;
		sf::Vector2f GetLinearVelocity() const;
		float		 GetRotation() const; // Returns rotation in degree

		bool ContainsPoint(sf::Vector2f point) const;

	private:
		b2Body*		m_body		= nullptr;
		b2Fixture*  m_fixture	= nullptr;
		Collider*   m_collider  = nullptr;

		void CopyBody(const RigidBody& other);
	};
}