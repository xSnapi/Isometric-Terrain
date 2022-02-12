#pragma once
#include <unordered_map>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "Heavy Text.hpp"

namespace hv {
	class TextArray : public sf::Drawable {
	public:
		TextArray();
		~TextArray();

		void SetFont(const sf::Font& font);
		void SetCharacterSize(uint32_t characterSize);

		void  AddText(const std::string& name, const std::string& str, sf::Vector2f position = sf::Vector2f());
		void  AddText(const std::string& name, const Text& text);
		Text& GetText(const std::string& name);

		void Clear();

		void DeleteText(const std::string& name);

		std::pair<const std::string, hv::Text>* begin();
		std::pair<const std::string, hv::Text>* end();

		Text& operator[](const std::string& name);

		void DisplayImGuiInfo();
	private:
		uint32_t		m_characterSize = 30;
		const sf::Font* m_font			= nullptr;

		std::unordered_map<std::string, Text> m_Texts;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}