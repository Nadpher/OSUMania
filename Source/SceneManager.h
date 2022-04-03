#ifndef OSUMANIA_SCENE_MANAGER_H
#define OSUMANIA_SCENE_MANAGER_H

#include <vector>
#include <memory>

#include "Scenes/Scene.h"
#include "Scenes/MainScene/MainScene.h"
#include "Scenes/PlayingScene/PlayingScene.h"
#include "Scenes/ScoreScene/ScoreScene.h"

namespace nadpher
{
	class SceneManager
	{
	public:

		static constexpr float transDuration = 2.0f;

		static SceneManager* getInstance()
		{
			static SceneManager* instance = new SceneManager;
			return instance;
		}

		std::unique_ptr<Scene>& getScene() { return scenes_[currentScene_]; }
		
		// rly ugly and bad
		void switchScene(unsigned int index, const std::string& beatmap = "", const unsigned int score = 0)
		{ 
			currentScene_ = index;

			switch (currentScene_)
			{
			case PLAYING_SCENE_INDEX:
				scenes_[currentScene_].reset(new PlayingScene(beatmap));
				break;

			case SCORE_SCENE_INDEX:
				scenes_[currentScene_].reset(new ScoreScene(score));
				break;

			default:
				break;
			}
		}

	private:

		SceneManager()
			: currentScene_(0)
		{
			scenes_.push_back(std::make_unique<MainScene>());
			scenes_.push_back(std::make_unique<PlayingScene>());
			scenes_.push_back(std::make_unique<ScoreScene>());
		}

		std::vector<std::unique_ptr<Scene>> scenes_;
		size_t currentScene_;
	};
}

#endif

