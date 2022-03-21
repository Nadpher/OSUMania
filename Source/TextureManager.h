#ifndef OSUMANIA_TEXTURE_MANAGER_H
#define OSUMANIA_TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <map>

namespace nadpher
{
	class TextureManager
	{
	public:
		TextureManager() = delete;

		static std::shared_ptr<sf::Texture>& get(const std::string& path);

	private:
		static std::map<std::string, std::shared_ptr<sf::Texture>> textures_;
	};
}

#endif
