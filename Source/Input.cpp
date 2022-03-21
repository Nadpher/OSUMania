#include "Input.h"

namespace nadpher
{
	std::map<sf::Keyboard::Key, bool> Input::keysPressed_;
	std::map<sf::Keyboard::Key, bool> Input::keysReleased_;
}