#ifndef OSUMANIA_SCORE_POPUP_H
#define OSUMANIA_SCORE_POPUP_H

#include <SFML/Graphics.hpp>

namespace nadpher
{
	class ScorePopUp : public sf::Drawable
	{
	public:
		ScorePopUp();

		void setPosition(const sf::Vector2f& position)
		{
			text_.setPosition(position);
		}

		void show(unsigned int score);
		void update();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		static constexpr float popUpDuration = 1.0f;

	private:

		sf::Text text_;
		float timer_;

	};
}

#endif
