#pragma once

/*
	Profile Timer.hpp
	High resolution timer used by heavy
	to measure time in function calls
*/

#include <chrono>
#include "Heavy Debug.hpp"

namespace hv {
	class ProfileTimer {
	public:
		ProfileTimer(const char* name) 
			:	m_duration(0.0f), m_name(name)
		{
			m_start = std::chrono::high_resolution_clock::now();
		}

		~ProfileTimer() 
		{
			m_end = std::chrono::high_resolution_clock::now();
			m_duration = m_end - m_start;

			float ms = m_duration.count() * 1000.0f;

			Color c = ms < 1000.0f ? Color::Green : ms < 5000.0f ? Color::Yellow : Color::Red;
			
			Debug::Log(c, "[Timer \"", m_name, "\" took ", ms, "ms]\n");
		}

	private:
		std::chrono::time_point<std::chrono::steady_clock> m_start;
		std::chrono::time_point<std::chrono::steady_clock> m_end;

		std::chrono::duration<float> m_duration;
		const char* m_name;
	};
}