#pragma once

/*
	Core definitions for Heavy Engine
	Every key macro or function should be placed here
*/

// Disables enum class warning
#pragma warning(disable: 26812)

// Linker /ignore:4006 removes warning that optick and SFML gave

#define ENABLE_IMGUI		 0
#define DISABLE_PROFILING	 1
#define DISABLE_CONSOLE		 1

#if DISABLE_PROFILING
	#define HV_PROFILE_FRAME(...)
	#define HV_PROFILE_FUNC(...)
	#define HV_PROFILE_TAG(NAME, ...)
	#define HV_PROFILE_THREAD(...)
	#define HV_PROFILE_SCOPE_DYNAMIC(NAME)
	#define HV_LOG(...)
	#define HV_ASSERT(VAR) VAR
	#define HV_DEBUG_ASSERT(VAR)
	#define HV_TIME_FUNC(NAME)
	#define HV_DEBUG(VAR)

#else
	#include <iostream>
	#include <SFML/System/Vector2.hpp>
	#include <SFML/System/Vector3.hpp>
	#include <SFML/Graphics/Color.hpp>
	#include <Optick/optick.h>
	#include "../include/Profile Timer.hpp"

	#define HV_PROFILE_FRAME(...)			OPTICK_FRAME(__VA_ARGS__)
	#define HV_PROFILE_FUNC(...)			OPTICK_EVENT(__VA_ARGS__)
	#define HV_PROFILE_TAG(NAME, ...)		OPTICK_TAG(NAME, __VA_ARGS__)
	#define HV_PROFILE_THREAD(...)			OPTICK_THREAD(__VA_ARGS__)
	#define HV_PROFILE_SCOPE_DYNAMIC(NAME)  OPTICK_EVENT_DYNAMIC(NAME)
	#define HV_LOG(...)						DEBUG_MESSAGE_LOG(__VA_ARGS__)
	#define HV_ASSERT(VAR) if(!(VAR))		__debugbreak();
	#define HV_DEBUG_ASSERT(VAR) if(!(VAR))	__debugbreak();
	#define HV_TIME_FUNC(NAME)				hv::ProfileTimer NAME(#NAME)
	#define HV_DEBUG(VAR)					VAR

	template<typename ...Args>
	constexpr static void DEBUG_MESSAGE_LOG(Args&&... args) 
	{
		(std::cout << ... << args);
	}

	template<typename T>
	static std::ostream& operator<<(std::ostream& out, const sf::Vector2<T>& vec) {
		out << "[X " << vec.x << ", Y " << vec.y << "]";
		return out;
	}
	
	template<typename T>
	static std::ostream& operator<<(std::ostream& out, const sf::Vector3<T>& vec) {
		out << "[X " << vec.x << ", Y " << vec.y << ", Z " << vec.z << "]";
		return out;
	}
	
	static std::ostream& operator<<(std::ostream& out, const sf::Color& color) {
		out << "[R " << (int)color.r << ", G " << (int)color.g << ", B " << (int)color.b << ", A " << (int)color.a << "]";
		return out;
	}

#endif

#if DISABLE_CONSOLE
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
