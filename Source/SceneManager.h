#ifndef OSUMANIA_SCENE_MANAGER_H
#define OSUMANIA_SCENE_MANAGER_H

#include <vector>
#include <memory>

#include "Scenes/Scene.h"
#include "Scenes/MainScene/MainScene.h"
#include "Scenes/PlayingScene/PlayingScene.h"
#include "Scenes/ScoreScene/ScoreScene.h"
#include "Scenes/EditScene/EditScene.h"

namespace nadpher
{
	// read up on observer pattern!
	class SceneManager
	{
	public:

		static SceneManager* getInstance()
		{
			static SceneManager* instance = new SceneManager;
			return instance;
		}

		Scene* getScene() const { return scenes_[currentScene_].get(); }
		
		void switchScene(unsigned int index)
		{ 
			// invalid index
			if (index > scenes_.size() - 1)
			{
				return;
			}

			currentScene_ = index;
			scenes_[currentScene_]->enter();
		}

	private:

		SceneManager()
			: currentScene_(0), scenes_{}
		{
			scenes_.push_back(std::make_unique<MainScene>());
			scenes_.push_back(std::make_unique<PlayingScene>());
			scenes_.push_back(std::make_unique<ScoreScene>());
			scenes_.push_back(std::make_unique<EditScene>());
		}

		std::vector<std::unique_ptr<Scene>> scenes_;
		unsigned int currentScene_;
	};
}

#endif

