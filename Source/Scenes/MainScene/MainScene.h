#ifndef OSUMANIA_MAIN_SCENE_H
#define OSUMANIA_MAIN_SCENE_H

#include "../Scene.h"

#include "Conductor.h"

namespace nadpher
{
	class MainScene : public Scene
	{
	public:
		MainScene();

		bool update();
		void end();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		static constexpr float judgementLinePosition = 500.0f;

	private:

		sf::VertexArray judgementLine_;

		Conductor conductor_;
	};
}

#endif

