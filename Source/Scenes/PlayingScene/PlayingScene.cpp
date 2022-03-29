#include "../../SceneManager.h"
#include "../../Input.h"

#include "PlayingScene.h"

namespace nadpher
{
	PlayingScene::PlayingScene(const char* beatmapPath)
	{
		if (beatmapPath == "")
		{
			return;
		}

		if (beatmap_.init(beatmapPath))
		{
			beatmap_.play();
		}
		else
		{
			SceneManager::getInstance()->switchScene(MAIN_SCENE_INDEX);
		}
	}

	bool PlayingScene::update()
	{
		switch (beatmap_.getBeatmapStatus())
		{
		case sf::SoundSource::Stopped:
			SceneManager::getInstance()->switchScene(MAIN_SCENE_INDEX);
			break;

		case sf::SoundSource::Paused:
			if (Input::isKeyDown(sf::Keyboard::Escape))
			{
				beatmap_.play();
			}

			break;

		case sf::SoundSource::Playing:
			beatmap_.update();

			if (Input::isKeyDown(sf::Keyboard::Escape))
			{
				beatmap_.pause();
			}

			break;

		default:
			break;
		}

		return true;
	}

	void PlayingScene::end()
	{

	}

	void PlayingScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(beatmap_);
	}
}