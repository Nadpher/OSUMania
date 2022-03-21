#include "TextureManager.h"

#include <spdlog/spdlog.h>

namespace nadpher
{
	std::map<std::string, std::shared_ptr<sf::Texture>> TextureManager::textures_;

	std::shared_ptr<sf::Texture>& TextureManager::get(const std::string& path)
	{
		if (textures_.find(path) == textures_.end())
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
}