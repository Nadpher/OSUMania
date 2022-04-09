#include "../../Input.h"
#include "../../SceneManager.h"

#include "EditScene.h"

#include "../MainScene/MainScene.h"

#include <spdlog/spdlog.h>

namespace nadpher
{
	void EditScene::enter()
	{
		std::string path = MainScene::getPath();
		if (!beatmap_.readFromDisk(path))
		{
			SceneManager::getInstance()->switchScene(MAIN_SCENE_INDEX);
		}
	}

	bool EditScene::update()
	{
		switch (beatmap_.getBeatmapStatus())
		{
		case sf::SoundSource::Paused:
		case sf::SoundSource::Stopped:
			if (Input::isKeyDown(sf::Keyboard::Space))
			{
				beatmap_.play();
			}
			break;

		case sf::SoundSource::Playing:
			if (Input::isKeyDown(sf::Keyboard::Space))
			{
				beatmap_.pause();
			}
			break;

		default:
			break;
		}

		return true;
	}

	void EditScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(beatmap_, states);
	}
}