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
		: conductor_("Songs/Test/song.ogg", 0.1f, 178.0f),
		  judgementLine_(sf::LinesStrip, 2)
	{
		sf::Vector2u bounds = Game::getBounds();

		judgementLine_[0].position = sf::Vector2f(0.0f, judgementLinePosition);
		judgementLine_[1].position = sf::Vector2f(Game::getBounds().x, judgementLinePosition);
	}

	bool MainScene::update()
	{
		conductor_.update();

		return true;
	}

	void MainScene::end()
	{

	}

	void MainScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(judgementLine_);
	}
}