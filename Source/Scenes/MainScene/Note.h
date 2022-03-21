#ifndef OSUMANIA_NOTE_H
#define OSUMANIA_NOTE_H

#include <SFML/Graphics.hpp>

namespace nadpher
{
	class Note : public sf::Drawable
	{
	public:

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		unsigned int lane_;
		float timePosition_;

		sf::Sprite sprite_;
	};
}

#endif

