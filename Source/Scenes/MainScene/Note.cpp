#include "Note.h"

namespace nadpher
{
	void Note::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite_);
	}
}