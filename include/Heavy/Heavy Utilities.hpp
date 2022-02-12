#pragma once

/*
	Heavy Utilities.hpp
	Class with conversions or functions that dosen't fit anywhere else,
	but are used pretty often
*/

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector3.hpp>

#include "Heavy Math.hpp"

namespace hv {
	inline sf::Color Vec3ToColor(const sf::Vector3f& v, sf::Uint8 alpha = 255) {
		return sf::Color((sf::Uint8)v.x, (sf::Uint8)v.y, (sf::Uint8)v.z, alpha);
	}

	inline sf::Vector3f ColorToVec3(const sf::Color& c) { // Note alpha is striped here
		return sf::Vector3f(c.r, c.g, c.b);
	}

	inline sf::Vector3f ColorToNormalizedVec3(const sf::Color& c) { // Note alpha is striped here
		return sf::Vector3f((float)c.r / 255.0f, (float)c.g / 255.0f, (float)c.b / 255.0f);
	}

	inline sf::Glsl::Vec4 ColorToNormalizedVec4(const sf::Color& c) {
		return sf::Glsl::Vec4((float)c.r / 255.0f, (float)c.g / 255.0f, (float)c.b / 255.0f, (float)c.a / 255.0f);
	}

	inline sf::Color NormalizedVec3ToColor(const sf::Vector3f& v) { // Note alpha is striped here
		float r = v.x >= 0.0f ? v.x > 1.0f ? 1.0f : v.x * 255.0f : 0.0f;
		float g = v.y >= 0.0f ? v.y > 1.0f ? 1.0f : v.y * 255.0f : 0.0f;
		float b = v.z >= 0.0f ? v.z > 1.0f ? 1.0f : v.z * 255.0f : 0.0f;

		return sf::Color((sf::Uint8)r, (sf::Uint8)g, (sf::Uint8)b, (sf::Uint8)255);
	}

	static sf::Color HueShift(const sf::Color& color, float shift) {

		sf::Vector3f normalizedColor = ColorToNormalizedVec3(color);

		const sf::Vector3f k(0.57735f, 0.57735f, 0.57735f);

		float cosAngle = cosf(shift);
		float sinAngle = sinf(shift);

		sf::Vector3f A = normalizedColor * cosAngle;
		sf::Vector3f B = CrossProduct(k, normalizedColor) * sinAngle;
		sf::Vector3f C = k * DotProduct(k, normalizedColor) * (1.0f - cosAngle);

		return NormalizedVec3ToColor(A + B + C);
	}

	static bool PointIntersect
	(
		const sf::Vector2f& point, 
		const sf::Vector2f& a, const sf::Vector2f& b, 
		const sf::Vector2f& c, const sf::Vector2f& d
	) 
	{
		//TODO: create
	}
}