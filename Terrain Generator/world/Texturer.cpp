#include "ispch.h"
#include "Texturer.hpp"

std::unordered_map<Texture, Texturer::Coords> Texturer::TexCoords;

void Texturer::Init(uint32_t sizeX, uint32_t sizeY, uint32_t size) {
	int i = sizeX / size;
	int j = sizeY / size;

	int k = 0;

	for (int y = 0; y < j; y++) {
		for (int x = 0; x < i; x++) {
			TexCoords[(Texture)k] =
			{
				sf::Vector2f(x * size + 0.0001f, y * size - 0.0001f),
				sf::Vector2f((x + 1) * size + 0.0001f, (y + 1) * size - 0.0001f)
			};

			k++;
		}
	}
}

Texturer::Texturer() {

}

Texturer::~Texturer() {

}
