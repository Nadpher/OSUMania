#include "FontManager.h"

#include <spdlog/spdlog.h>

namespace nadpher
{
	std::map<std::string, std::shared_ptr<sf::Font>> FontManager::fonts_;

	std::shared_ptr<sf::Font>& FontManager::get(const std::string& path)
	{
		if (fonts_.find(path) == fonts_.end())
		{
			sf::Font font;
			if (!font.loadFromFile(path))
			{
				spdlog::error("Couldn't open font {}", path);
			}

			fonts_.insert({ path, std::make_shared<sf::Font>(font) });
		}

		return fonts_[path];
	}
}