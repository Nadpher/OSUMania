#ifndef OSUMANIA_PLAYING_SCENE_H
#define OSUMANIA_PLAYING_SCENE_H

#include "../Scene.h"

#include "Beatmap.h"

namespace nadpher
{
	class PlayingScene : public Scene
	{
	public:
		PlayingScene(const char* beatmapPath = "");

		bool update() override;
		void end() override;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		Beatmap beatmap_;
	};
}

#endif
