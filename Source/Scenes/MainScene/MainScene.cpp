#include "../../Game.h"
#include "../../Input.h"

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
			notes_.push_back({ conductor_, crotchet * (i + 5), 1000.0f });
		}

		judgementLine_[0].position = sf::Vector2f(0.0f, judgementLinePosition);
		judgementLine_[1].position = sf::Vector2f(Game::getBounds().x, judgementLinePosition);
	}

	bool MainScene::update()
	{
		conductor_.update();

		for (Note& note : notes_)
		{
			note.update();
		}

		if (Input::isKeyPressed(sf::Keyboard::Z) && !notes_.empty() && !hitNote_)
		{
			hitNote_ = judgeNote();
			if (hitNote_)
			{
				notes_.pop_front();
			}
		}

		if (Input::isKeyReleased(sf::Keyboard::Z))
		{
			hitNote_ = false;
		}

		return true;
	}

	bool MainScene::judgeNote()
	{
		if (std::abs(notes_.front().getTimePosition() - conductor_.getSongPosition()) < perfectTreshold)
		{
			spdlog::info("Perfect");
			return true;
		}
		
		if (std::abs(notes_.front().getTimePosition() - conductor_.getSongPosition()) < goodTreshold)
		{
			spdlog::info("Good");
			return true;
		}

		if (std::abs(notes_.front().getTimePosition() - conductor_.getSongPosition()) < okTreshold)
		{
			spdlog::info("Ok");
			return true;
		}

		if (std::abs(notes_.front().getTimePosition() - conductor_.getSongPosition()) < mehTreshold)
		{
			spdlog::info("Meh");
			return true;
		}

		return false;
	}

	void MainScene::end()
	{

	}

	void MainScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(judgementLine_);
		for (const Note& note : notes_)
		{
			target.draw(note);
		}
	}
}