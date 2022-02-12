#pragma once

/*
	Timer.hpp
	Timer repeats it's given function every period of time
*/

#include <functional>

namespace hv {
	class Timer {
	public:
		Timer();
		~Timer();

		void Update();
		void SetUpdateTime(const float& time);
		void SetFunction(std::function<void()> fun);

		void Restart();

		float GetUpdateTime() const;
		std::function<void()> GetFunction() const;
	private:
		float m_elapsedTime = 0.0f;
		float m_updateTime = 9999.9f;

		std::function<void()> m_fun;
	};
}