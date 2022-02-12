#pragma once

#include <fstream>
#include <unordered_map>
#include <list>

namespace hv {
	class IniParser {
	public:
		IniParser();

		IniParser(const std::string& path);

		~IniParser();

		bool Open(const std::string& path);
		bool Close();

		bool Save();
		void Clear();

		void Set(const std::string& str , const std::string& section, const std::string& parametr);
		void Set(const int& var			, const std::string& section, const std::string& parametr);
		void Set(const float& var		, const std::string& section, const std::string& parametr);
		void Set(const sf::Vector2f& vec, const std::string& section, const std::string& parametr);
		void Set(const sf::Vector3f& vec, const std::string& section, const std::string& parametr);
		void Set(const sf::Color&  color, const std::string& section, const std::string& parametr);

		std::string  GetStr	  (const std::string& section, const std::string& parametr) const;
		int			 GetInt	  (const std::string& section, const std::string& parametr) const;
		float		 GetFloat (const std::string& section, const std::string& parametr) const;
		sf::Vector2f GetVec2  (const std::string& section, const std::string& parametr) const;
		sf::Vector3f GetVec3  (const std::string& section, const std::string& parametr) const;
		sf::Color	 GetColor (const std::string& section, const std::string& parametr) const;

	private:
		// Cashe memory designed not to use linear search in vectors
		// Sections with parametrs and values
		std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_Sections;

		// Because of unordered_map behavior we keep order of sections in list
		std::list<std::string>									m_SectionOrder;
		std::unordered_map<std::string, std::list<std::string>> m_ParametrOrder;

		std::fstream m_file;
		std::string  m_path;
		bool		 m_open = false;

		// Warning handling for given section and parametr I know setting parametr can be made through this but I would have to do warnings other way
		const std::string* GetParametr(const std::string& section, const std::string& parametr) const;

		void SetParametr(const std::string& section, const std::string& parametr, const std::string& parsedParametr);

		bool CheckFile() const;
		void Load();
		void Parse(std::vector<std::string>& Lines);
	};
}