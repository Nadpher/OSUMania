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

		static constexpr float judgementLinePosition = 500.0f;
		static constexpr float noteVelocity = 500.0f;

		static constexpr float laneOffset = 350.0f;
		static constexpr size_t lanesSize = 4;

	private:

		sf::VertexArray judgementLine_;
		std::array<Lane, lanesSize> lanes_;
		Conductor conductor_;
	};
}

#endif

