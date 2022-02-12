#pragma once
#include <SFML/System/Vector2.hpp>

#include "Light World.hpp"

namespace hv {
	struct LightEdge 
	{
		LightEdge();

		LightEdge(sf::Vector2f start, sf::Vector2f end);

		LightEdge(const LightEdge& other);

		~LightEdge();

		LightEdge* operator=(const LightEdge& other);

		void Set(sf::Vector2f start, sf::Vector2f end);

		void SetStart(sf::Vector2f start);
		void SetEnd(sf::Vector2f end);

		sf::Vector2f GetStart() const;
		sf::Vector2f GetEnd() const;
	private:
		Edge* m_edge = nullptr;

		void CopyEdge(const LightEdge& other);
	};
}

namespace hv {
	struct PointLight
	{
		PointLight();

		PointLight(sf::Vector2f pos);

		PointLight(float radius);

		PointLight(sf::Vector2f pos, float radius);

		PointLight(const PointLight& other);

		~PointLight();

		PointLight* operator=(const PointLight& other);

		void SetPosition(sf::Vector2f pos);
		void SetRadius(float radius);
		void SetAttenuation(float attenuation);
		void SetPower(float power);
		void SetDrawable(bool drawable);
		void SetColor(sf::Color color);

		sf::Vector2f GetPosition() const;
		float GetRadius() const;
		float GetAttenuation() const;
		float GetPower() const;
		bool  GetDrawable() const;

		void DisplayImGuiInfo(const std::string& tabName);
	private:
		Light* m_light = nullptr;

		void CopyLight(const PointLight& other);
	};
}