#include "../../Game.h"

#include "MainScene.h"
#include "Note.h"

#include <random>
#include <spdlog/spdlog.h>

namespace nadpher
{
	std::random_device dev;
	std::mt19937 rng;
	std::uniform_int_distribution<unsigned int> dist(0, 255);

	MainScene::MainScene()
		: conductor_("Songs/Test/song.ogg", 0.1f, 178.0f)
	{
		sf::Vector2u bounds = Game::getBounds();
		strobe_.setSize({ (float)bounds.x, (float)bounds.y });

	}

	bool MainScene::update()
	{
		conductor_.update();

		static float counter = 0.0f;

		if (conductor_.getSongPosition() > counter + conductor_.getCrotchet())
		{
			strobe_.setFillColor(sf::Color(dist(rng), dist(rng), dist(rng), 255));

			counter += conductor_.getCrotchet();
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