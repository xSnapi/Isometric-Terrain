#pragma once

/*
	Camera.hpp
	Singleton class responsible for camera and it's effects
*/

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <Heavy Math.hpp>

#include "Heavy Renderer.hpp"

namespace hv {
	class Camera {
	public:
		static Camera& Get();
		void Init(Renderer& renderer);

		void Update();

		// Cammera shake effect
		void Shake(float time, int power);

		// Modifiers
		void Move(sf::Vector2f offset);
		void Zoom(float zoom);
		void SetPosition(sf::Vector2f position);

		// Accessors
		sf::Vector2f GetCenter() const;
		sf::Vector2f GetSize() const;
		float GetZoom() const;
	private:
		Camera();
		~Camera();

		struct ShakeContext 
		{
			sf::Vector2f Center;
			sf::Vector2f Pos[6];
			uint32_t CurrentPos = 0;

			void CreatePos(const int& power);
		};

		sf::View m_view;

		Renderer* m_renderer = nullptr;

		sf::Vector2f m_moveOffset;

		float m_zoom = 1.0f;

		float m_shakeElapsedTime = 0.0f;
		float m_shakeTime = 0.0f;

		static Camera s_instance;

		void ApplyEffects();
		void Shake();
		ShakeContext m_sc;

		void Resize(const sf::Vector2f& size);

		Mat4x4 Projection;
	};
}