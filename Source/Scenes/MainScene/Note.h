#ifndef OSUMANIA_NOTE_H
#define OSUMANIA_NOTE_H

#include <SFML/Graphics.hpp>

namespace nadpher
{
	class Conductor;

	class Note : public sf::Drawable
	{
	public:
		Note(unsigned int lane = 0, float timePosition = 0.0f, float speed = 0.0f);

		void update(Conductor& conductor);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		unsigned int getLane() const { return lane_; }

	private:

		// TODO: Implement command pattern!!!!!!
		const unsigned int lane_;
		const float timePosition_;
		const float speed_;

		sf::Vector2f worldPosition_;
		sf::Sprite sprite_;
	};
}

#endif

