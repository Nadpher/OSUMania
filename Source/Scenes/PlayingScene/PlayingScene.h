#ifndef OSUMANIA_PLAYING_SCENE_H
#define OSUMANIA_PLAYING_SCENE_H

#include "../Scene.h"

#include "Beatmap.h"
#include "ScorePopUp.h"

#include <string>
#include <array>

namespace nadpher
{
	class PlayingScene : public Scene
	{
	public:
		PlayingScene(const std::string& beatmapPath = "");

		bool update() override;
		void end() override;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		static constexpr float cooldownTime = 2.0f;

	private:
		void handlePausedState();
		bool handlePlayingState();

		void animateGuides();

		float cooldownTimer_;

		Beatmap beatmap_;
		ScorePopUp popUp_;
		std::array<sf::Sprite, Beatmap::lanesNum> judgementGuides_;

		bool isInitialized_;
	};
}

#endif
