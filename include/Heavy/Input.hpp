#pragma once

/*
	Key Check.hpp
	Class checking for user input can read it in not-repeating mode
*/

#include <unordered_map>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Heavy Renderer.hpp"

namespace hv {
	class Input {
	public:
		class Keyboard {
		public:
			// Repeat ~true~ dosen't make function blok checked key
			static bool KeyCheck(sf::Keyboard::Key key, bool repeat = false);
		};

		class Mouse {
		public:
			// Repeat ~true~ dosen't make function blok checked button
			static bool KeyCheck(sf::Mouse::Button key, bool repeat = false);

			// Returns mouse position relative to window maped to coords
			static sf::Vector2f GetRelativePosition();

			// Returns mouse position relative to window
			static sf::Vector2f GetRelativeCoords();

			// Returns mouse position NOT RELATIVE TO WINDOW
			static sf::Vector2f GetPosition();

			// Returns mouse position NOT RELATIVE TO WINDOW maped to coords
			static sf::Vector2f GetCoords();

			static void DisplayImGuiInfo(const std::string& tabName);
		};

		static void Init(sf::RenderWindow& window, Renderer& renderer);
		static void Update();
		static void BlockInput();

	private:
		static std::unordered_map<sf::Mouse::Button, bool> s_Buttons;
		static std::unordered_map<sf::Keyboard::Key, bool> s_Keys;

		const static sf::RenderWindow*  s_window;
		const static Renderer*			s_renderer;
	};
}