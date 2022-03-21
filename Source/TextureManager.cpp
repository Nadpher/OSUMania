#include "TextureManager.h"

#include <spdlog/spdlog.h>

namespace nadpher
{
	std::map<std::string, std::shared_ptr<sf::Texture>> TextureManager::textures_ = {};

}