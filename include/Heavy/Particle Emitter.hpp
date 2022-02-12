#pragma once

/*
	Particle Emitter.hpp
	Creates and emitts particles
*/

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

namespace hv {
	class ParticleEmitter;

	enum class MovementType
	{
		Linear = 0,
		SmoothStop
	};

	struct Particle
	{
		float Velocity	= 1.0f;

		float Size		= 1.0f;
		float SizeScale = 1.0f;

		float Opacity		= 1.0f;
		float OpacityTarget = 0.0f;

		float LifeTimeMin = 0.0f;
		float LifeTimeMax = 1.0f;

		sf::Color BirthColor = sf::Color::White;
		sf::Color DeathColor = sf::Color::White;

		sf::Vector2f Direction;

		MovementType MovementType = MovementType::SmoothStop;

		sf::Texture* Texture = nullptr;
	};
}

namespace hv {
	class ParticleEmitter : public sf::Drawable {
	public:

		ParticleEmitter(sf::Vector2f position, Particle particle = Particle());

		ParticleEmitter();

		~ParticleEmitter();
		
		void Update();
		void Emitt();

		void SetParticleSpawnTime(float time);
		void SetParticleLimit(uint32_t limit);

	private:
		struct ParticleProp 
		{
			float Velocity		 = 0.0f;

			float RotationTarget = 0.0f;
			float Rotation		 = 0.0f;

			float SizeTarget	= 1.0f;
			float Size			= 1.0f;

			float Opacity		= 1.0f;
			float OpacityTarget = 0.0f;

			float LifeTimeRemaining = 0.0f;
			float LifeTime			= 0.0f;
			float Life				= 1.0f;

			sf::Color DeathColor;
			sf::Color BirthColor;

			sf::Vector2f Scale = sf::Vector2f(1.0f, 1.0f);

			sf::Vector2f Position;
			sf::Vector2f Direction;

			sf::Vertex Vertices[6];
		};

		std::vector<ParticleProp> m_Particles;

		sf::Vector2f m_position;

		float m_elapsedTime = 0.0f;
		float m_spawnTime   = 0.1f;

		float m_spread		= 0.8f;
		
		uint32_t m_limit = 1;

		Particle m_particle = Particle();

		void CreateParticle();

		void Resize(size_t size);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}