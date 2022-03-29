#include <spdlog/spdlog.h>
#include <imgui-SFML.h>

#include "Game.h"
#include "Input.h"

#include "SceneManager.h"

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

			// makes sure input only takes single key presses
			Input::refreshInput();

			handleEvents();

			ImGui::SFML::Update(window_, elapsed);

			if (!SceneManager::getInstance()->getScene()->update())
			{
				window_.close();
				break;
			}

			window_.clear();
			window_.draw(*SceneManager::getInstance()->getScene());

			ImGui::SFML::Render(window_);
			window_.display();
		}

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
				Input::keysDown_[event.key.code] = true;
				break;

			case sf::Event::KeyReleased:
				Input::keysUp_[event.key.code] = true;
				break;

			case sf::Event::Resized:
				windowSize_.x = event.size.width;
				windowSize_.y = event.size.height;
				break;

			default:
				break;
			}
		}
	}
}