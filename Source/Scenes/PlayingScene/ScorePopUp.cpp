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

		// y Position is an arbitrary value
		text_.setPosition({ (float)Game::getBounds().x / 2.0f, 100.0f });

		
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

		// center text
		sf::FloatRect rect = text_.getLocalBounds();
		text_.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
	}

	void ScorePopUp::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(text_);
	}
}