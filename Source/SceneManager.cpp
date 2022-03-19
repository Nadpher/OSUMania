#include "SceneManager.h"

namespace nadpher
{
	std::vector<std::unique_ptr<Scene>> SceneManager::scenes_ = {};
								 size_t	SceneManager::currentScene_ = 0;
}