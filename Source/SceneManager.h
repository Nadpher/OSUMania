#ifndef OSUMANIA_SCENE_MANAGER_H
#define OSUMANIA_SCENE_MANAGER_H

#include <vector>
#include <memory>

#include "Scenes/Scene.h"
#include "Scenes/MainScene/MainScene.h"
#include "Scenes/PlayingScene/PlayingScene.h"

namespace nadpher
{
	class SceneManager
	{
	public:

		static SceneManager* getInstance()
		{
			static SceneManager* instance = new SceneManager;
			return instance;
		}

		std::unique_ptr<Scene>& getScene() { return scenes_[currentScene_]; }
		
		void resetScene() { scenes_[currentScene_].reset(); }
		void setScene(unsigned int index) { currentScene_ = index; }

	private:

		SceneManager()
			: currentScene_(0)
		{
			scenes_.push_back(std::make_unique<MainScene>());
			scenes_.push_back(std::make_unique<PlayingScene>());
		}

		std::vector<std::unique_ptr<Scene>> scenes_;
		size_t currentScene_;
	};
}

#endif

