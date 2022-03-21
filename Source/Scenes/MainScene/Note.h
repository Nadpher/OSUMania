#ifndef OSUMANIA_NOTE_H
#define OSUMANIA_NOTE_H

#include <SFML/Graphics.hpp>

namespace nadpher
{
	class Note : public sf::Drawable
	{
	public:
		Note(unsigned int lane = 0, float timePosition = 0.0f);

		void update();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		unsigned int getLane() const { return lane_; }
		float getTimePosition() const { return timePosition_; }

	private:

		// TODO: Implement command pattern!!!!!!
		const unsigned int lane_;
		float timePosition_;

		sf::Vector2f worldPosition_;
		sf::Sprite sprite_;
	};
}

#endif

