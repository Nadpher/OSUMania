#ifndef OSUMANIA_PLAYING_SCENE_H
#define OSUMANIA_PLAYING_SCENE_H

#include "../Scene.h"

#include "Beatmap.h"

namespace nadpher
{
	class PlayingScene : public Scene
	{
	public:

		bool update() override;

	private:
		Beatmap beatmap_;
	};
}

#endif
