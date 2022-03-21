#include <spdlog/spdlog.h>

#include "Game.h"

#include "SceneManager.h"
#include "Input.h"

#include "Scenes/MainScene/Note.h"

namespace nadpher
{
	sf::RenderWindow Game::window_;
	float	         Game::deltaTime_;

	bool Game::init(unsigned int width, unsigned int height, const char* title)
	{
		window_.create(sf::VideoMode(width, height), title);
		if (!window_.isOpen())
		{
			spdlog::error("Couldn't create SFML window");
			return false;
		}

		return true;
	}

	void Game::run()
	{
		sf::Clock clock;
		Note test(0, 1);

		while (window_.isOpen())
		{
			sf::Time elapsed = clock.restart();
			deltaTime_ = elapsed.asSeconds();

			handleEvents();

			if (!SceneManager::getInstance()->getScene()->update())
			{
				SceneManager::getInstance()->getScene()->end();
			}

			test.update();

			window_.clear();
			window_.draw(*SceneManager::getInstance()->getScene());
			window_.draw(test);
			window_.display();
		}
	}

	void Game::handleEvents()
	{
		sf::Event event;
		while (window_.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window_.close();
				break;

			case sf::Event::KeyPressed:
				Input::keysPressed_[event.key.code] = true;
				break;

			case sf::Event::KeyReleased:
				Input::keysReleased_[event.key.code] = true;
				break;

			default:
				break;
			}
		}
	}
}