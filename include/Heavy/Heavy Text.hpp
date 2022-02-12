#pragma once
#include <string>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

namespace hv {
	class Text : public sf::Text {
	public:
		Text();

		Text(const std::string& str, const sf::Font& font);

		Text(const std::string& str, const sf::Font& font, sf::Vector2f position);

		~Text();

		// Modifiers
		void setFont(const sf::Font& font);
		void setFont(const sf::Font& font, uint32_t characterSize);
		void setSmooth(bool var);
		void setCharacterSize(uint32_t characterSize);
		void setString(const std::string& str);

		// Accessors
		sf::Vector2f getSize() const;

		void DisplayImGuiInfo(const std::string& tabName);

	private:
		typedef sf::Text m_text;

		bool m_smooth = false;

		void CorrectAlignment();
	};
}