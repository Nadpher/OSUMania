#ifndef OSUMANIA_EDIT_SCENE_H
#define OSUMANIA_EDIT_SCENE_H

#include "../Scene.h"
#include "../Beatmap.h"

#include <string>

namespace nadpher
{
	class EditScene : public Scene
	{
	public:
		EditScene();

		void enter() override;
		bool update() override;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:

		void handleStoppedState();
		void reloadPositions();
		void autoHit();

		bool changed_;
		Beatmap beatmap_;
		std::array<sf::Sprite, Beatmap::lanesNum> judgementGuides_;
	};
}

#endif

