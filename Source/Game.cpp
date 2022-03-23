#include <spdlog/spdlog.h>
#include <imgui-SFML.h>

#include "Game.h"

#include "SceneManager.h"
#include "Input.h"

#include "Scenes/MainScene/Note.h"


namespace nadpher
{
	sf::RenderWindow Game::window_;
	sf::Vector2u	 Game::windowSize_;
	float	         Game::deltaTime_;

	bool Game::init(unsigned int width, unsigned int height, const char* title)
	{
		spdlog::set_level(spdlog::level::debug);

		window_.create(sf::VideoMode(width, height), title);
		if (!window_.isOpen())
		{
			spdlog::error("Couldn't create SFML window");
			return false;
		}

		windowSize_ = { width, height };

		ImGui::SFML::Init(window_);

		return true;
	}

	void Game::run()
	{
		sf::Clock clock;

		window_.setKeyRepeatEnabled(false);
		while (window_.isOpen())
		{
			sf::Time elapsed = clock.restart();
			deltaTime_ = elapsed.asSeconds();

			handleEvents();

			ImGui::SFML::Update(window_, elapsed);

			if (!SceneManager::getInstance()->getScene()->update())
			{
				SceneManager::getInstance()->getScene()->end();
			}

			window_.clear();
			window_.draw(*SceneManager::getInstance()->getScene());

			ImGui::SFML::Render(window_);
			window_.display();
		}

		if (window_.isOpen()) window_.close();


	}

	void Game::handleEvents()
	{
		sf::Event event;
		while (window_.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			switch (event.type)
			{
			case sf::Event::Closed:
				window_.close();
				break;

			case sf::Event::KeyPressed:
				Input::keysPressed_[event.key.code] = true;
				Input::keysReleased_[event.key.code] = false;
				break;

			case sf::Event::KeyReleased:
				Input::keysReleased_[event.key.code] = true;
				Input::keysPressed_[event.key.code] = false;
				break;

			default:
				break;
			}
		}
	}
}