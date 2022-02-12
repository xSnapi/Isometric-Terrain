#pragma once
#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

namespace hv {
	//TODO: find way to change to private
	class Renderer : public sf::RenderTexture {
	public:
		using sf::RenderTexture::draw;
		using sf::RenderTexture::display;

		sf::Color ClearColor;

		Renderer();
		~Renderer();

		void draw(const std::string& str, const sf::Vector2f& position, const sf::Color& color = sf::Color::White);
		void plainDraw(const sf::Drawable& drawable, sf::RenderStates states = sf::RenderStates::Default);
		void clear();

		sf::RenderWindow& GetWindow() const;
		void SetWindow(sf::RenderWindow& window);
		void LoadFont(const std::string& path);
		void Resize(sf::Vector2u size);
		const sf::Sprite& GetFrame();

		static void DrawCircle(sf::RenderTarget& target, sf::Vector2f position, float radius, sf::Color color = sf::Color::White, bool diagonalBar = true);
	private:
		typedef sf::RenderTexture m_frame;

		sf::Sprite m_frameSprite;

		sf::Font*  m_font = nullptr;
		sf::Text   m_text;

		sf::RenderWindow* m_window = nullptr;
	};
}