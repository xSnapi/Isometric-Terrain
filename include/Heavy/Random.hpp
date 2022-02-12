#pragma once

/*
	Random.hpp
	Singleton class featuring simple random number generator
*/

#include <random>

namespace hv {
	class Random {
	public:
		static Random& Get();

		int Int(int min, int max);
		float Float(float min, float max);
		double Double(double min, double max);

	private:
		Random();
		~Random();

		std::mt19937 m_randomEngine;

		static Random s_instance;
	};
}