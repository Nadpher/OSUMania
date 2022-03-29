#ifndef OSUMANIA_SCENE_H
#define OSUMANIA_SCENE_H

#include <SFML/Graphics.hpp>

#define MAIN_SCENE_INDEX 0
#define PLAYING_SCENE_INDEX 1
#define EDITOR_SCENE_INDEX 2

namespace nadpher
{
	class Scene : public sf::Drawable
	{
	public:

		virtual bool update() = 0;
		virtual void end() = 0;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	};
}

#endif
