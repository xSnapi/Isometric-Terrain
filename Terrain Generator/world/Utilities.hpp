#pragma once

#include <SFML/System/Vector2.hpp>

static sf::Vector2f CartesianToIsometric(float x, float y, float size) {
	return sf::Vector2f
	(
		(x - y) * size * 0.5f,
		(x + y) * size * 0.25f
	);
}

static sf::Vector2f IsometricToCartesian(float x, float y, float size) {
	return sf::Vector2f
	(
		 x / size + (2.0f * y) / size,
		-x / size + (2.0f * y) / size
	);
}