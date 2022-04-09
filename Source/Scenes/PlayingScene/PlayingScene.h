#ifndef OSUMANIA_PLAYING_SCENE_H
#define OSUMANIA_PLAYING_SCENE_H

#include "../Scene.h"
#include "../Beatmap.h"

#include "ScorePopUp.h"

#include <string>
#include <array>

namespace nadpher
{
	class PlayingScene : public Scene
	{
	public:
		PlayingScene();

		bool update() override;
		void enter() override;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		static unsigned int getScore() { return score_; }

	private:
		void handlePausedState();
		bool handlePlayingState();

		void handleInput();
		void animateGuides();

		static unsigned int score_;

		Beatmap beatmap_;
		ScorePopUp popUp_;
		std::array<sf::Sprite, Beatmap::lanesNum> judgementGuides_;
	};
}

#endif
