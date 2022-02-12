#pragma once

/*
	Event Dispatcher.hpp
	Class giving access to last event
*/

#include <unordered_set>
#include <unordered_map>

#include <SFML/Window/Event.hpp>

namespace hv {
	class EventDispatcher {
	public:
		static void Init(bool& focus);

		static void DispatchEvent(const sf::Event& event);

		static sf::Event GetEvent(sf::Event::EventType type);
		static bool CheckFor(sf::Event::EventType event);
		static void Clear();

	private:
		static bool* s_focus;
		static std::unordered_map<sf::Event::EventType, sf::Event> s_events;
	};
}