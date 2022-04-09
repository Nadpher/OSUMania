#ifndef OSUMANIA_SCORE_SCENE_H
#define OSUMANIA_SCORE_SCENE_H

#include "../Scene.h"

namespace nadpher
{
	class ScoreScene : public Scene
	{
	public:
		ScoreScene();

		bool update() override;
		void enter() override;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Text scoreText_;
	};
}

#endif

