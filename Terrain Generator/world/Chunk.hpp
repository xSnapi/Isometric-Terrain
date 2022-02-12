#pragma once

#include "ispch.h"
#include <SFML/Graphics/VertexBuffer.hpp>

#include "Perlin Noise.hpp"
#include "Texturer.hpp"

struct Block 
{
	struct Info
	{
		const static uint32_t Size = 20;
	};

	Block(uint32_t index, uint32_t x, uint32_t y)
		: Index(index)
		, X(x)
		, Y(y)
	{

	}

	uint32_t Index = 0;
	uint32_t X = 0;
	uint32_t Y = 0;
};

class Chunk : public sf::Drawable {
public:

	struct Info
	{
		const static uint32_t Size = 16;
	};

	static siv::PerlinNoise* PerlinNoise;

	Chunk();

	Chunk(sf::Vector2f position);

	~Chunk();

	void Create(sf::Vector2f position);

	void Update();

private:
	std::vector<sf::Vertex> m_Vertices;

	std::vector<Block> m_WaterBlocks;

	sf::VertexBuffer m_vertexBuffer;

	sf::Vector2f m_position;

	static sf::Clock m_clock;

	void UpdateWater();

	void AddCube(sf::Vector2f position, float size, sf::Color color = sf::Color::White, Texturer::Coords texCoords = { });

	void CreateTree(sf::Vector2f coords);

	static sf::Color GetBlockColor(int height);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};