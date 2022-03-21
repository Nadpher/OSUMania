#ifndef OSUMANIA_GAME_H
#define OSUMANIA_GAME_H

#include <SFML/Graphics.hpp>

namespace nadpher
{
	class Game
	{
	public:

		static bool init(unsigned int width, unsigned int height, const char* title = "OSU Mania");
		static void run();

		static void quit() { window_.close(); }

		static float getDeltaTime() { return deltaTime_; }

	private:

		static void handleEvents();

		static float deltaTime_;
		static sf::RenderWindow window_;
	};
}

#endif
