#include "../../Game.h"

#include "MainScene.h"
#include "Note.h"

#include <random>
#include <spdlog/spdlog.h>

namespace nadpher
{
	MainScene::MainScene()
		: conductor_("Songs/Test/song.ogg", 178.0f)
	{
		sf::Vector2u bounds = Game::getBounds();
		strobe_.setSize({ (float)bounds.x, (float)bounds.y });

	}

	bool MainScene::update()
	{
		conductor_.update();

		spdlog::info("Song position: {}", conductor_.getSongPosition());

		if ((int)(conductor_.getSongPosition() * 100) % (int)conductor_.getBPM())
		{
			std::random_device dev;
			std::mt19937 rng;
			std::uniform_int_distribution<unsigned int> dist(0, 255);

			strobe_.setFillColor(sf::Color(dist(rng), dist(rng), dist(rng), 255));
		}

		return true;
	}

	void MainScene::end()
	{

	}

	void MainScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(strobe_);
	}
}