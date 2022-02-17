#include "ispch.h"
#include "Map.hpp"

#include "Utilities.hpp"

#include "Texturer.hpp"

Map::Map(hv::Renderer& renderer)
	: m_renderer(renderer)
	, m_chunkOrigin(WINDOW_WIDTH / 2.0f, 425.0f / 2.0f) // Please do not ask why is 425 here
{
	hv::Camera::Get().Move(sf::Vector2f(0.1f, 0.1f));

	InitNoise();
	InitTexturer();
}

Map::~Map() {

}

void Map::Update() {
	static int renderDist = 7; // works for now

	static bool update = true;

	if (hv::Input::Keyboard::KeyCheck(sf::Keyboard::V))
		update = !update;

	if (hv::Input::Keyboard::KeyCheck(sf::Keyboard::Up, true))
		renderDist++;
	else if (hv::Input::Keyboard::KeyCheck(sf::Keyboard::Down))
		renderDist--;

	sf::Vector2f cameraPos(hv::Camera::Get().GetCenter() - m_chunkOrigin);

	sf::Vector2i coord = IsometricToCartesian(cameraPos.x, cameraPos.y, (float)Chunk::Info::Size * (float)Block::Info::Size);

	m_ChunksToRender.clear();

	for (int y = -renderDist + coord.y; y <= renderDist + coord.y; y++) {
		for (int x = -renderDist + coord.x; x <= renderDist + coord.x; x++) {

			if (m_Chunks.find(sf::Vector2i(x, y)) == m_Chunks.end()) {
				sf::Vector2f coords = CartesianToIsometric((float)x, (float)y, (float)Chunk::Info::Size * (float)Block::Info::Size);

				m_Chunks[sf::Vector2i(x, y)].Create(coords + m_chunkOrigin);
				if(update)
					m_Chunks[sf::Vector2i(x, y)].Update();
			}

			m_ChunksToRender.push_back(&m_Chunks[sf::Vector2i(x, y)]);
		}
	}

	if (!update)
		return;

	static float tick = 0.15f;
	static float elapsedTime = 0.0f;

	elapsedTime += hv::dt;

	if (elapsedTime >= tick) {
		for (auto& r : m_ChunksToRender)
			r->Update();

		elapsedTime -= tick;
	}
}

void Map::Render() {
	

	sf::RenderStates states;
	states.texture = &hv::TextureLibrary::Get().Res("block_atlas");

	for (auto& r : m_ChunksToRender)
		m_renderer.draw(*r, states);
}

void Map::InitNoise() {
	Chunk::PerlinNoise = new siv::PerlinNoise(hv::Random::Get().Int(0, std::numeric_limits<int>().max()));
}

void Map::InitTexturer() {
	auto& t = hv::TextureLibrary::Get().Res("block_atlas");

	sf::Vector2u s = t.getSize();

	Texturer::Init(s.x, s.y, 100);
}
