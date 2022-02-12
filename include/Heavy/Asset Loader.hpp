#pragma once

/*
	Asset Loader.hpp
	Singleton class responsible for asynchronous asset load
*/

#include <SFML/Graphics/Shader.hpp>

#include <future>
#include <functional>
#include <stack>

#include "Core.hpp"

namespace hv {
	enum class AssetType
	{
		Texture = 0,
		Font,
		Music,
		Sound,
		Shader,
		MemoryShader,
	};

	class AssetLoader {
	public:
		static AssetLoader& Get();

		// This function synchronizes all threads
		void Sync();

		// You can load only one type of resource at the call of this function
		// if you are using it to load shader fragment always must be on the left side!
		void AddResource(std::string name, std::string path, AssetType type);
		void AddResource(const std::string& name, const std::string& fragment, const std::string& vertex, AssetType type);
	private:
		AssetLoader();
		~AssetLoader();

		struct Resource 
		{
			void(*Fun)(void*, std::string) = 0;
			void* Raw = 0;
		};

		std::stack<std::future<void>> m_Results;

		Resource GetResource(const std::string& name, const AssetType& type);

		static void LoadTexture (void* res, std::string path);
		static void LoadFont	(void* res, std::string path);
		static void LoadMusic	(void* res, std::string path);
		static void LoadSound	(void* res, std::string path);

		static void LoadShader  (sf::Shader* res, std::string fragment, std::string vertex);
		static void LoadShaderFromMemory(sf::Shader* res, std::string fragment, std::string vertex);

		static AssetLoader s_instance;
	};
}