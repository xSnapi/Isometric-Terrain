#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <box2d/b2_world.h>

#include "b2_draw.hpp"

/*
	Simple difference between light and physic world is that
	Physics world is just abstraction of b2 World class
*/

namespace hv {
	class  RigidBody;
	class  Runtime;
	struct EdgeCollider;

	class PhysicsWorld {
	public:
		static PhysicsWorld& Get();

		template<typename ...T>
		void EnableDebugDraw(T&&... args) {
			uint32_t size = sizeof...(args);

			if (size > 4)
				return;

			uint32_t sum = 0;

			DebugDrawType buffer[] = { Refactor(args)... };

			for (uint32_t i = 0; i < size; i++)
				sum += GetB2DrawType(buffer[i]);

			m_debugDraw.SetFlags(sum);
			m_debugDrawEnabled = true;
		}

		void DisableDebugDraw();

	private:
		PhysicsWorld();
		~PhysicsWorld();

		b2World m_world;

		b2DebugDraw  m_debugDraw;
		bool		 m_debugDrawEnabled = false;

		template<typename T>
		DebugDrawType Refactor(T const& t) {
			DebugDrawType buffer;

			buffer = t;

			return buffer;
		}

		void InitDebugDraw(sf::RenderWindow& window);

		uint32_t GetB2DrawType(DebugDrawType type) const;

		friend class  RigidBody;
		friend class  Runtime;
		friend struct EdgeCollider;

		static PhysicsWorld s_instance;
	};
}