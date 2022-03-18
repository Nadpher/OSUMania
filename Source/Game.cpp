#include "Game.h"

#include <spdlog/spdlog.h>

namespace nadpher
{
	sf::RenderWindow Game::window_;

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

		while (window_.isOpen())
		{
			sf::Time elapsed = clock.restart();
			float deltaTime = elapsed.asSeconds();

			handleEvents();

			window_.clear();

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

			default:
				break;
			}
		}
	}
}