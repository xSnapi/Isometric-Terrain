#pragma once

#include <SFML/System/Clock.hpp>

/*
	Fixed Clock.hpp
	Fixed Clcok measuring time based on delta time of application
*/

namespace hv {
	class FixedClock {
	public:
		FixedClock(bool start);
		~FixedClock();

		void Start();
		void Stop();
		void Restart();

		sf::Time GetElapsedTime() const;
	private:
		sf::Clock m_clock;
		sf::Time m_stoppedTime = sf::Time::Zero;
		bool m_running = false;
	};
}