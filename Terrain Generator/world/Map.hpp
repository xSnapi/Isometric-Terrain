#pragma once

#include "ispch.h"

#include "Chunk.hpp"

namespace std {
	template<> struct hash<sf::Vector2i> {
		std::size_t operator()(const sf::Vector2i& p) const noexcept {
			return (size_t)(p.x + p.y);
		}
	};
}

class Map {
public:
	Map(hv::Renderer& renderer);
	~Map();

	void Update();
	void Render();

private:
	std::unordered_map<sf::Vector2i, Chunk> m_Chunks;
	std::vector<Chunk*> m_ChunksToRender;

	sf::Vector2f m_chunkOrigin;

	hv::Renderer& m_renderer;

	void InitNoise();
	void InitTexturer();
};