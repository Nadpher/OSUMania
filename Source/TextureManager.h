#ifndef OSUMANIA_TEXTURE_MANAGER_H
#define OSUMANIA_TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

#include <memory>
#include <string>
#include <map>

namespace nadpher
{
	class TextureManager
	{
	public:
		static std::shared_ptr<sf::Texture>& get(const std::string& path)
		{
			if (!textures_.count(path))
			{
				sf::Texture texture;
				if (!texture.loadFromFile(path))
				{
					spdlog::error("Couldn't load texture {}", path);
				}

				textures_.insert({ path, std::make_shared<sf::Texture>(texture) });
			}

			return textures_[path];
		}

	private:
		static std::map<std::string, std::shared_ptr<sf::Texture>> textures_;

	};
}

#endif
