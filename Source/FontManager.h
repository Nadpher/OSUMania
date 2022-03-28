#ifndef OSUMANIA_FONT_MANAGER_H
#define OSUMANIA_FONT_MANAGER_H

#include <SFML/Graphics.hpp>

#include <string>
#include <memory>
#include <map>

namespace nadpher
{
	class FontManager
	{
	public:
		static std::shared_ptr<sf::Font>& get(const std::string& path);

	private:
		static std::map<std::string, std::shared_ptr<sf::Font>> fonts_;
	};
}

#endif

