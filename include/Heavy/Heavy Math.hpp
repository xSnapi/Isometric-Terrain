#pragma once

/*
	Heavy Math.hpp
	Class with simple math functions
*/

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

// Math in here dosen't seem heavy, but the engine is ¯\_(ツ)_/¯

constexpr float HV_PI = 3.141592f;

namespace hv {

	template<typename T, uint32_t S>
	struct Column
	{
		T& operator[](uint32_t i) {
			return m_value[i];
		}

	private:
		T m_value[S] = { 0.0f };
	};

	template<uint32_t S, uint32_t W>
	struct Mat
	{
		Column<float, S>& operator[](uint32_t i) {
			return m_col[i];
		}

	protected:
		Column<float, W> m_col[S];
	};

	struct Mat4x4 : public Mat<4, 4> {

	};

	struct Mat3x3 : public Mat<3, 3> {
		sf::Vector3f operator * (sf::Vector3f vec) {
			return sf::Vector3f
			(
				m_col[0][0] * vec.x + m_col[1][0] * vec.y + m_col[2][0] * vec.z,
				m_col[0][1] * vec.x + m_col[1][1] * vec.y + m_col[2][1] * vec.z,
				m_col[0][2] * vec.x + m_col[1][2] * vec.y + m_col[2][2] * vec.z
			);
		}
	};

	struct Mat2x2 : public Mat<2, 2> {
		sf::Vector2f operator * (sf::Vector2f vec) {
			return sf::Vector2f
			(
				m_col[0][0] * vec.x + m_col[1][0] * vec.y,
				m_col[0][1] * vec.x + m_col[1][1] * vec.y
			);
		}
	};



	static Mat4x4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
		Mat4x4 proj;

		proj[0][0] = 2.0f / (right - left);
		proj[1][1] = 2.0f / (top - bottom);
		proj[2][2] = -2.0f / (zFar - zNear);
		// x idzie pierwszy potem y

		proj[3][0] = -(right + left) / (right - left);
		proj[3][1] = -(top + bottom) / (top - bottom);
		proj[3][2] = -(zFar + zNear) / (zFar - zNear);

		proj[3][3] = 1.0f;

		return proj;
	}

	inline float Length(const sf::Vector2f v) {
		return sqrt((v.x * v.x) + (v.y * v.y));
	}

	static float Smoothstep(float a0, float a1, float x) {
		float t = std::clamp<float>((x - a0) / (a1 - a0), 0.0f, 1.0f);

		return t * t * (3.0f - 2.0f * t);
	}

	static float Distance(const sf::Vector2f& v0, const sf::Vector2f& v1) { // Distance between two points
		if (v0.x == v1.x)
			return fabs(v0.y - v1.y);
		else if (v0.y == v1.y)
			return fabs(v0.x - v1.x);

		return sqrtf((v0 - v1).x * (v0 - v1).x + (v0 - v1).y * (v0 - v1).y);
	}

	inline float Sign(const float& var) {
		return var / abs(var);
	}

	inline sf::Vector2f Sign(const sf::Vector2f& var) {
		return sf::Vector2f(var.x / abs(var.x), var.y / abs(var.y));
	}

	static sf::Vector2f Abs(sf::Vector2f v) {
		v.x = (v.x < 0.0f ? -v.x : v.x);
		v.y = (v.y < 0.0f ? -v.y : v.y);

		return v;
	}

	inline float CrossProduct(const sf::Vector2f& v0, const sf::Vector2f& v1) {
		return v0.x * v1.y - v0.y * v1.x;
	}

	inline sf::Vector3f CrossProduct(const sf::Vector3f& v0, const sf::Vector3f& v1) {
		return sf::Vector3f
		(
			v0.y * v1.z - v0.z * v1.y,
			v0.z * v1.x - v0.x * v1.z,
			v0.x * v1.y - v0.y * v1.x
		);
	}

	static sf::Vector2f normalize(const sf::Vector2f& v) {
		float length = Length(v);

		return length != 0.0f ? sf::Vector2f(v.x / length, v.y / length) : v;
	}

	inline float DotProduct(const sf::Vector2f& v0, const sf::Vector2f& v1) {
		return v0.x * v1.x + v0.y * v1.y;
	}

	inline float DotProduct(const sf::Vector3f& v0, const sf::Vector3f& v1) {
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
	}

	inline float Lerp(const float& x, const float& y, const float& t) { // Linear interpolation
		return x * (1.0f - t) + y * t;
	}

	inline sf::Vector2f Lerp(const sf::Vector2f& x, const sf::Vector2f& y, const float& t) {
		return x * (1.0f - t) + y * t;
	}

	inline sf::Vector3f Lerp(const sf::Vector3f& x, const sf::Vector3f& y, const float& t) {
		return x * (1.0f - t) + y * t;
	}
}
