#ifndef OSUMANIA_INPUT_H
#define OSUMANIA_INPUT_H

#include <SFML/Window.hpp>

#include <map>

// Input handler for single key presses
namespace nadpher
{
	class Input
	{
	public:

		static void refreshInput();

		static bool isKeyDown(sf::Keyboard::Key key);
		static bool isKeyUp(sf::Keyboard::Key key);

	private:
		static std::map<sf::Keyboard::Key, bool> keysDown_;
		static std::map<sf::Keyboard::Key, bool> keysUp_;

		friend class Game;
	};
}

#endif