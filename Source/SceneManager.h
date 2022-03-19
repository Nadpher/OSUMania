#ifndef OSUMANIA_SCENE_MANAGER_H
#define OSUMANIA_SCENE_MANAGER_H

#include <vector>
#include <memory>

#include "Scenes/Scene.h"

namespace nadpher
{
	class SceneManager
	{
	public:

		static std::unique_ptr<Scene>& getScene() { return scenes_[currentScene_]; }

	private:

		static std::vector<std::unique_ptr<Scene>> scenes_;
		static size_t currentScene_;
	};
}

#endif

