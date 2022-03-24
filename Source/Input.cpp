#include "Input.h"

namespace nadpher
{
	std::map<sf::Keyboard::Key, bool> Input::keysDown_;
	std::map<sf::Keyboard::Key, bool> Input::keysUp_;

	void Input::refreshInput()
	{
		// Disables continued keys down presses
		for (auto it = keysDown_.begin(); it != keysDown_.end(); ++it)
		{
			if (it->second)
			{
				it->second = false;
			}
		}

		// Disables continued keys up presses
		for (auto it = keysUp_.begin(); it != keysUp_.end(); ++it)
		{
			if (it->second)
			{
				it->second = false;
			}
		}
	}

	bool Input::isKeyDown(sf::Keyboard::Key key)
	{
		if (keysDown_.find(key) != keysDown_.end())
		{
			return keysDown_[key];
		}

		return false;
	}

	bool Input::isKeyUp(sf::Keyboard::Key key)
	{
		if (keysUp_.find(key) != keysUp_.end())
		{
			return keysUp_[key];
		}

		return false;
	}
}