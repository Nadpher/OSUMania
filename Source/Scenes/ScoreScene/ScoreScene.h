#ifndef OSUMANIA_SCORE_SCENE_H
#define OSUMANIA_SCORE_SCENE_H

#include "../Scene.h"

namespace nadpher
{
	class ScoreScene : public Scene
	{
	public:
		ScoreScene(unsigned int score = 0);

		bool update() override;
		void end() override;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Text scoreText_;
	};
}

#endif

