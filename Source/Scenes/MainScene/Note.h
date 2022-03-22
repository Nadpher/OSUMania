#ifndef OSUMANIA_NOTE_H
#define OSUMANIA_NOTE_H

#include <SFML/Graphics.hpp>

namespace nadpher
{
	class Conductor;

	class Note : public sf::Drawable
	{
	public:
		Note(const Conductor& conductor, float timePosition = 0.0f, float velocity = 1.0f);

		void update();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		const float getTimePosition() const { return timePosition_; }

	private:

		// TODO: Implement command pattern!!!!!!
		const float timePosition_;
		const float velocity_;

		sf::Vector2f worldPosition_;
		sf::Sprite sprite_;
	};
}

#endif

