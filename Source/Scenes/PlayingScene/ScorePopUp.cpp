#include "../../FontManager.h"
#include "../../Game.h"

#include "ScorePopUp.h"

namespace nadpher
{
	ScorePopUp::ScorePopUp()
		: timer_(0.0f)
	{
		text_.setFont(*FontManager::get("Resource/Fonts/scoreFont.ttf"));

		text_.setCharacterSize(64);
	}

	void ScorePopUp::update()
	{
		if (timer_ > 0.0f)
		{
			timer_ -= Game::getDeltaTime();
		}
		else
		{
			hide();
		}
	}

	void ScorePopUp::show(unsigned int score)
	{
		if (!score)
		{
			text_.setString("Miss");
		}
		else
		{
			text_.setString(std::to_string(score));
		}

		timer_ = popUpDuration;
		text_.setFillColor(sf::Color::White);
	}

	void ScorePopUp::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(text_);
	}
}