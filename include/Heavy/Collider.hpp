#pragma once

/*
	Collider.hpp
*/

#include <functional>
#include <vector>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

#include "Heavy Box2D.hpp"

namespace hv {
	class RigidBody;

	namespace Constants {
		constexpr float PPM = 30.0f; // Pixel per meter
	}
}

namespace hv {
	class Collider {
	public:
		Collider();
		virtual ~Collider();

		virtual void SetTriggered(bool triggered);

		std::function<void()> OnTriggerStart;
		std::function<void()> OnTriggerEnd;

		void SetRestitution(float restitution);
	protected:
		b2FixtureDef i_fixtureDef;

		friend class RigidBody;
	};
}

namespace hv {
	struct BoxCollider : public Collider {
	public:
		BoxCollider();

		BoxCollider(sf::Vector2f size);

		~BoxCollider();

		void SetSize(sf::Vector2f size);

	private:
		b2PolygonShape m_shape;
	};
}

namespace hv {
	struct CircleCollider : public Collider {
	public:
		CircleCollider();

		CircleCollider(float radius);

		~CircleCollider();

		// Modifiers

		void SetRadius(float radius);

	private:
		b2CircleShape m_shape;
	};
}

namespace hv {
	struct EdgeCollider : public Collider {
	public:
		EdgeCollider();

		~EdgeCollider();

		// Modifiers
		void AddPoints(sf::Vector2f start, sf::Vector2f end);
		void DeletePoint(size_t index);
		//void GetPoint(size_t index);
		void SetPoint(sf::Vector2f start, sf::Vector2f end, size_t index);
		void Clear();

		std::vector<b2Fixture*>& Raw();
	private:
		b2EdgeShape m_shape;
		b2Body* m_body;

		std::vector<b2Fixture*> m_Fixtures;
	};
}

namespace hv {
	class ContactListener : public b2ContactListener {
	public:
		virtual void BeginContact(b2Contact* contact);
		virtual void EndContact(b2Contact* contact);
	};
}