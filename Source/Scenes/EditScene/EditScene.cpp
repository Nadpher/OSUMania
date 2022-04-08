#include "../../Input.h"

#include "EditScene.h"

#include <spdlog/spdlog.h>

namespace nadpher
{
	EditScene::EditScene(const std::string& path)
	{
		if (path == "")
		{
			return;
		}

		if (!beatmap_.song_.openFromFile(path))
		{
			spdlog::error("Couldn't open {}", path);
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

	void EditScene::end()
	{

	}

	void EditScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(beatmap_, states);
	}
}