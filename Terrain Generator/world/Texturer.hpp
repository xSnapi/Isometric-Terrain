#pragma once

#include "ispch.h"

enum class Texture 
{
	Block,
	PlainBlock,
	Grass,
	Poppy,
};

class Texturer {
public:

	struct Coords
	{
		sf::Vector2f Start;
		sf::Vector2f End;
	};

	static void Init(uint32_t sizeX, uint32_t sizeY, uint32_t size = 100);

	static std::unordered_map<Texture, Coords> TexCoords;

private:
	Texturer();
	~Texturer();

};