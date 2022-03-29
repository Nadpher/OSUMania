#ifndef OSUMANIA_MAIN_SCENE_H
#define OSUMANIA_MAIN_SCENE_H

#include "../Scene.h"

namespace nadpher
{
	class MainScene : public Scene
	{
	public:
		MainScene();

		bool update() override;
		void end() override;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};
}

#endif

