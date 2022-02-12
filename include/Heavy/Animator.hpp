#pragma once
#include <functional>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace hv {
	struct Animation;

	class Animator {
	public:
		float DefaultSpeed = 0.0f;

		Animator();

		Animator(float defaultSpeed);

		~Animator();

		void Play(Animation& animation);
	private:

		void Update(Animation& animation);
		void UpdateReverse(Animation& animation);

		bool Check(const Animation& animation);

		float m_animationSpeed = 0.0f;
	};
}

namespace hv {
	enum class SpriteSheet { RightDown = 0, DownRight };

	struct Animation
	{
		float Speed = 0.0f;

		bool PlayOnce = false;
		bool Reversed = false;
		bool Playable = true;

		int32_t  CurrentFrame = 0;
		uint32_t FrameCount   = 0;

		uint32_t FrameWidth  = 0;
		uint32_t FrameHeight = 0;

		sf::Sprite*  Sprite = nullptr;
		sf::IntRect* Frames = nullptr;

		std::function<void()> OnStart	= 0;
		std::function<void()> OnEnd		= 0;

		void Create(uint32_t frameCountX, uint32_t frameCountY, SpriteSheet mode = SpriteSheet::RightDown, uint32_t offset = 0,
			sf::Sprite* sprite = nullptr, sf::Texture* texture = nullptr);

		void ApplyFrame(const sf::IntRect& frame);

		void Restart(bool frame = false);

		void DisplayImGuiInfo(const std::string& tabName);

		Animation* operator=(const Animation& animation);

		Animation();

		Animation(const Animation& animation);

		~Animation();

	private:
		float m_elapsedTime = 0.0f;

		void CopyAnimation(const Animation& other);

		friend class Animator;
	};
}