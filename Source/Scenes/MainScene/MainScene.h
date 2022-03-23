#ifndef OSUMANIA_MAIN_SCENE_H
#define OSUMANIA_MAIN_SCENE_H

#include "../Scene.h"

#include "Conductor.h"
#include "Note.h"
#include "Lane.h"

#include <array>

namespace nadpher
{
	class MainScene : public Scene
	{
	public:
		MainScene();

		bool update();
		void end();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	private:

	};
}

#endif

