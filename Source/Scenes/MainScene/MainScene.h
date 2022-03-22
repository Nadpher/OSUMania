#ifndef OSUMANIA_MAIN_SCENE_H
#define OSUMANIA_MAIN_SCENE_H

#include <deque>

#include "../Scene.h"

#include "Conductor.h"
#include "Note.h"

namespace nadpher
{
	class MainScene : public Scene
	{
	public:
		MainScene();

		bool update();
		void end();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		static constexpr float mehTreshold = 0.3f;
		static constexpr float okTreshold = 0.2f;
		static constexpr float goodTreshold = 0.1f;
		static constexpr float perfectTreshold = 0.05f;

		static constexpr float judgementLinePosition = 500.0f;
		static constexpr float noteVelocity = 500.0f;

	private:

		bool hitNote_;

		bool judgeNote();

		sf::VertexArray judgementLine_;
		std::deque<Note> notes_;

		Conductor conductor_;
	};
}

#endif

