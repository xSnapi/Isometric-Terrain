#include "ispch.h"
#include "Chunk.hpp"

#include "Utilities.hpp"

siv::PerlinNoise* Chunk::PerlinNoise = nullptr;
sf::Clock Chunk::m_clock;

Chunk::Chunk() {

}

Chunk::Chunk(sf::Vector2f position) {
	Create(position);
}

Chunk::~Chunk() {

}

void Chunk::Update() {
	UpdateWater();

	m_vertexBuffer.update(m_Vertices.data());
}

void Chunk::Create(sf::Vector2f position) {
	m_Vertices.reserve(1000);

	m_position = position;

	constexpr double Freq = 0.001;
	constexpr int	 WaterLevel = 2;

	float BlockSize = Block::Info::Size;
	float ChunkSize = Chunk::Info::Size;

	for (int x = 0; x < ChunkSize; x++) {
		for (int y = 0; y < ChunkSize; y++) {
			sf::Vector2f coords(CartesianToIsometric((float)x, (float)y, Block::Info::Size));

			coords += m_position;

			double noise = PerlinNoise->octave2D_01
			(
				coords.x * Freq, 
				coords.y * Freq, 
				6,
				0.45
			);

			noise = pow(noise, 4);

			int height = int(noise * 1300.0) / (int)BlockSize;

			// Here we add water
			if (height <= WaterLevel) {
				coords.y += BlockSize / 5.0f;

				noise = pow(noise, 0.2);

				noise += 0.45;

				const sf::Vector3f waterEdge (75.0f, 147.0f, 250.0f);
				const sf::Vector3f waterMidle(13.0f, 36.0f, 69.0f);

				m_WaterBlocks.emplace_back(m_Vertices.size(), x, y);

				AddCube
				(
					coords, 
					BlockSize, 
					hv::Vec3ToColor(hv::Lerp(waterMidle, waterEdge, (float)noise)), 
					Texturer::TexCoords[Texture::PlainBlock]
				);

				continue;
			}

			if (height > 4 && height <= 21 && !hv::Random::Get().Int(0, 245)) {
				coords.y -= (height - WaterLevel - 2) * BlockSize * 0.5f; // I have no idea why is -2 here

				CreateTree(coords);
				continue;
			}

			for (int j = WaterLevel; j < height; j++) {
				Texturer::Coords texCoords = Texturer::TexCoords[Texture::Block];

				sf::Color color = GetBlockColor(height - WaterLevel);

				if (j + 1 == height && height > 4 && height <= 21) {
					if (hv::Random::Get().Int(0, 3))
						continue;

					texCoords = !hv::Random::Get().Int(0, 8) ? Texturer::TexCoords[Texture::Poppy] : Texturer::TexCoords[Texture::Grass];
					color	  = sf::Color::White;
				}

				AddCube
				(
					coords, 
					BlockSize, 
					color,
					texCoords
				);

				coords.y -= BlockSize * 0.5f;
			}
		}
	}

	{
		m_vertexBuffer.setUsage(sf::VertexBuffer::Usage::Stream);
		m_vertexBuffer.setPrimitiveType(sf::Triangles);

		m_vertexBuffer.create(m_Vertices.size());
		m_vertexBuffer.update(m_Vertices.data());
	}
}

void Chunk::UpdateWater() {
	float size = Block::Info::Size / 2.0f;

	for (auto& b : m_WaterBlocks) {
		size_t index = b.Index;

		sf::Vector2f coords(CartesianToIsometric((float)b.X, (float)b.Y, Block::Info::Size));

		sf::Vector2f offset
		(
			0.0f,  
			6.0f * sinf(2.0f * m_clock.getElapsedTime().asSeconds() + (coords.y + m_position.y) * 7.5f)
		);

		sf::Vector2f position = coords + offset + m_position;

		auto& v = m_Vertices;

		v[index + 0].position = sf::Vector2f(-size, 0.0f)		 + position;
		v[index + 1].position = sf::Vector2f( size, 0.0f)		 + position;
		v[index + 2].position = sf::Vector2f( size, size * 2.0f) + position;

		v[index + 3].position = sf::Vector2f(-size, 0.0f)		 + position;
		v[index + 4].position = sf::Vector2f(-size, size * 2.0f) + position;
		v[index + 5].position = sf::Vector2f( size, size * 2.0f) + position;
	}
}

void Chunk::AddCube(sf::Vector2f position, float size, sf::Color color, Texturer::Coords texCoords) {
	size /= 2.0f;

	sf::Vertex v[6] =
	{
		{ sf::Vector2f(-size, 0.0f)		   + position, color, sf::Vector2f(texCoords.Start.x, texCoords.Start.y) },
		{ sf::Vector2f( size, 0.0f)		   + position, color, sf::Vector2f(texCoords.End.x,   texCoords.Start.y) },
		{ sf::Vector2f( size, size * 2.0f) + position, color, sf::Vector2f(texCoords.End.x,   texCoords.End.y)   },

		{ sf::Vector2f(-size, 0.0f)		   + position, color, sf::Vector2f(texCoords.Start.x, texCoords.Start.y) },
		{ sf::Vector2f(-size, size * 2.0f) + position, color, sf::Vector2f(texCoords.Start.x, texCoords.End.y)	 },
		{ sf::Vector2f( size, size * 2.0f) + position, color, sf::Vector2f(texCoords.End.x,   texCoords.End.y)	 },
	};


	for (uint32_t i = 0; i < 6; i++)
		m_Vertices.push_back(v[i]);
}

void Chunk::CreateTree(sf::Vector2f coords) {
	float BlockSize = (float)Block::Info::Size;

	sf::Color trunkColor(128, 89, 32);
	sf::Color leavesColor(76, 194, 33);

	float radius = 3.0f;

	bool big = false;

	//if 0 create Birch tree
	if (!hv::Random::Get().Int(0, 6)) {
		trunkColor  = sf::Color(201, 196, 171);
		leavesColor = sf::Color(131, 194, 112);

		if (!hv::Random::Get().Int(0, 5)) {
			trunkColor = sf::Color(66, 48, 27);
			leavesColor = sf::Color(38, 79, 26);

			big = true;
			radius = 7.65f;
		}
	}

	if (big) {
		int bigTrunkSize = 1;

		for (int y = -bigTrunkSize; y <= bigTrunkSize; y++) {
			for (int x = -bigTrunkSize; x <= bigTrunkSize; x++) {
				for (int z = 0; z <= 20; z++) {
					int coordX = x;
					int coordY = y;

					if (z > 2 && z < 10) {
						if (x == y || -x == y)
							continue;
					}
					else if (z >= 1) {
						if (x == y || -x == y) {
							if(!hv::Random::Get().Int(0, 1))
								continue;
						}
					}

					sf::Vector2f newCoords = CartesianToIsometric(coordX, coordY, BlockSize);

					AddCube
					(
						coords + newCoords - sf::Vector2f(0.0f, z * BlockSize * 0.5f),
						BlockSize,
						trunkColor,
						Texturer::TexCoords[Texture::Block]
					);
				}
			}
		}

		coords.y -= BlockSize * 20 * 0.5f;
	}
	else {
		for (int i = 0; i < 7; i++) {
			coords.y -= BlockSize * 0.5f;

			AddCube
			(
				coords,
				BlockSize,
				trunkColor,
				Texturer::TexCoords[Texture::Block]
			);

		}
	}

	for (int y = -radius; y <= radius; y++) {
		for (int x = -radius; x <= radius; x++) {
			for (int z = -radius; z <= radius; z++) {
				sf::Vector2f newCoords = CartesianToIsometric(x, y , BlockSize);

				if (x * x + y * y + z * z > radius * radius - 3.1f)
					continue;

				AddCube
				(
					coords + newCoords - sf::Vector2f(0.0f, z * BlockSize * 0.5f),
					BlockSize,
					leavesColor,
					Texturer::TexCoords[Texture::Block]
				);
			}
		}
	}
	
}

sf::Color Chunk::GetBlockColor(int height) {
	sf::Vector3f primary;
	sf::Vector3f secondary;
	float max = 1;

	if (height <= 2) { // Sand
		primary   = sf::Vector3f(237.0f, 200.0f, 55.0f);
		secondary = sf::Vector3f(207.0f, 171.0f, 31.0f);
		max = 2.0f;
	}
	else if (height <= 21) { // Grass
		primary   = sf::Vector3f(34.0f, 112.0f, 16.0f);
		secondary = sf::Vector3f(74.0f, 176.0f, 51.0f);
		max = 21.0f;
	}
	else if (height <= 29) { // Mountain
		primary   = sf::Vector3f(59, 59, 59);
		secondary = sf::Vector3f(166, 166, 166);
		max = 29.0f;
	}
	else { // Top	
		primary   = sf::Vector3f(209, 209, 209);
		secondary = sf::Vector3f(255, 255, 255);
	}

	if (height > max)
		max = height;

	return hv::Vec3ToColor(hv::Lerp(primary, secondary, height / max));
}

void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_vertexBuffer, states);
}
