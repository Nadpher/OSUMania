#ifndef OSUMANIA_INPUT_H
#define OSUMANIA_INPUT_H

#include <SFML/Window.hpp>
#include <map>

namespace nadpher
{
	class Input
	{
	public:
		bool isKeyPressed(const sf::Keyboard::Key& key) const { return keysPressed_[key]; }
		bool isKeyReleased(const sf::Keyboard::Key& key) const { return keysReleased_[key]; }

	private:

		static std::map<sf::Keyboard::Key, bool> keysPressed_;
		static std::map<sf::Keyboard::Key, bool> keysReleased_;

		friend class Game;
	};
}

#endif

