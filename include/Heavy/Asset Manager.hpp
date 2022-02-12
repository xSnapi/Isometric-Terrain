#pragma once

/*
	Asset Manager.hpp
	Singleton class responsible for managing assets
*/

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Soundbuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include <unordered_map>
#include <vector>
#include <string>

namespace hv {
	template<typename T>
	static bool Exists(const std::string& name, const std::unordered_map<std::string, T>& Resource) {
		if (Resource.find(name) == Resource.end())
			return true;

		hv::Debug::Log(hv::Color::Yellow, "[Resource ", name, " already exists skipping]\n");
		return false;
	}
}

namespace hv {
	template<typename T>
	class ResourceLibrary {
	public:
		ResourceLibrary() { };
		~ResourceLibrary() { };

		// Loads asset
		virtual void Load(std::string name, const char* path) = 0;

		// Deletes asset of given name
		virtual void Unload(const char* name) { i_Resources.erase(name); }

		// Clears map 
		virtual void Clear() { i_Resources.clear(); }

		// Returns current number of assets in map
		virtual size_t Size() { return i_Resources.size(); }

		// Returns reference to unordered_map with assets
		virtual std::unordered_map<std::string, T>& Raw() { return i_Resources; }

		// Returns reference to asset of given name
		// Assert here is called when you are trying to access not existing asset (only for debug mode tho)
		virtual T& Res(const char* name) { HV_DEBUG_ASSERT(i_Resources.find(name) != i_Resources.end()); return i_Resources[name]; };

	protected:
		std::unordered_map<std::string, T> i_Resources;
	};
}

namespace hv {
	class ShaderLibrary : public ResourceLibrary<sf::Shader> {
	public:
		static ShaderLibrary& Get() { return s_instance; }

		virtual void Load(std::string name, const char* path);

		void Load(std::string name, const char* fragmentPath, const char* vertexPath);
		void LoadFromMemory(std::string name, const char* fragment, const char* vertex);

	private:
		ShaderLibrary() { };
		~ShaderLibrary() { };

		static ShaderLibrary s_instance;
	};
}

namespace hv {
	class TextureLibrary : public ResourceLibrary<sf::Texture> {
	public:
		static TextureLibrary& Get() { return s_instance; }

		virtual void Load(std::string name, const char* path) { HV_DEBUG(if (!Exists(name, i_Resources)) return;); i_Resources[name].loadFromFile(path); }

	private:
		TextureLibrary() { };
		~TextureLibrary() { };

		static TextureLibrary s_instance;
	};
}

namespace hv {
	class FontLibrary : public ResourceLibrary<sf::Font> {
	public:
		static FontLibrary& Get() { return s_instance; }

		virtual void Load(std::string name, const char* path) { HV_DEBUG(if (!Exists(name, i_Resources)) return;); i_Resources[name].loadFromFile(path); }

	private:
		FontLibrary() { };
		~FontLibrary() { };

		static FontLibrary s_instance;
	};
}

namespace hv {
	struct SoundPack
	{
		sf::SoundBuffer SoundBuffer;
		sf::Sound		Sound;
	};

	class SoundLibrary {
	public:
		static SoundLibrary& Get() { return s_instance; }

		void Update(const float& soundVol = 100.0f, const float& musicVol = 100.0f);

		void ClearSounds();
		void ClearMusics();

		void LoadSound(std::string name, const char* path);
		void LoadMusic(std::string name, const char* path);

		SoundPack& Sound(const char* name);
		sf::Music& Music(const char* name);

		std::unordered_map<std::string, sf::Music>& RawMusic();
		std::unordered_map<std::string, SoundPack>& RawSound();

	private:
		SoundLibrary() { };
		~SoundLibrary();

		std::unordered_map<std::string, sf::Music> m_Musics;
		std::unordered_map<std::string, SoundPack> m_Sounds;

		static SoundLibrary s_instance;
	};
}