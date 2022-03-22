#ifndef OSUMANIA_INPUT_H
#define OSUMANIA_INPUT_H

#include <SFML/Window.hpp>
#include <map>

namespace nadpher
{
	class Input
	{
	public:
		static bool isKeyPressed(const sf::Keyboard::Key& key) { return keysPressed_[key]; }
		static bool isKeyReleased(const sf::Keyboard::Key& key) { return keysReleased_[key]; }

	private:

		static std::map<sf::Keyboard::Key, bool> keysPressed_;
		static std::map<sf::Keyboard::Key, bool> keysReleased_;

		friend class Game;
	};
}

#endif

