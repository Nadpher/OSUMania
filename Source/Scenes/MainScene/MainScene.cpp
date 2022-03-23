#include "../../Game.h"
#include "../../Input.h"
#include "../../TextureManager.h"

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

		float crotchet = conductor_.getCrotchet();

		// generates notes on each beat
		for (int i = 0; i < 8; ++i)
		{
			lanes_[i % 4].addNote({conductor_, crotchet * (i + 5), 1000.0f, i % 4u});
		}

		judgementLine_[0].position = sf::Vector2f(0.0f, judgementLinePosition);
		judgementLine_[1].position = sf::Vector2f(Game::getBounds().x, judgementLinePosition);
	}

	bool MainScene::update()
	{
		conductor_.update();

		for (Lane& lane : lanes_)
		{
			lane.update();
		}

		if (Input::isKeyPressed(sf::Keyboard::Z))
		{
			if (lanes_[0].judgeNote(conductor_))
			{
				lanes_[0].popNote();
			}
		}

		if (Input::isKeyPressed(sf::Keyboard::X))
		{
			if (lanes_[1].judgeNote(conductor_))
			{
				lanes_[1].popNote();
			}
		}

		if (Input::isKeyPressed(sf::Keyboard::N))
		{
			if (lanes_[2].judgeNote(conductor_))
			{
				lanes_[2].popNote();
			}
		}

		if (Input::isKeyPressed(sf::Keyboard::M))
		{
			if (lanes_[3].judgeNote(conductor_))
			{
				lanes_[3].popNote();
			}
		}

		return true;
	}

	void MainScene::end()
	{

	}

	void MainScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(judgementLine_);
		for (const Lane& lane : lanes_)
		{
			target.draw(lane);
		}
	}
}