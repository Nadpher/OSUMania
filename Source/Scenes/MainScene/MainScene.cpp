#include "../../Game.h"
#include "../../TextureManager.h"
#include "../../Input.h"

#include "MainScene.h"
#include "Note.h"

#include <spdlog/spdlog.h>

#include <imgui.h>

namespace nadpher
{
	MainScene::MainScene()
	{
		sf::Vector2u bounds = Game::getBounds();
		if (beatmap_.init("Songs/Test/"))
		{
			beatmap_.play();
		}
	}

	bool MainScene::update()
	{
		switch (beatmap_.getBeatmapStatus())
		{
		case sf::SoundSource::Stopped:
			ImGui::Begin("Select a song...");
			ImGui::End();

			break;

		case sf::SoundSource::Playing:
			beatmap_.update();

			if (Input::isKeyDown(sf::Keyboard::Key::Escape))
			{
				beatmap_.pause();
			}

			break;

		case sf::SoundSource::Paused:
			if (Input::isKeyDown(sf::Keyboard::Key::Escape))
			{
				beatmap_.play();
			}

			ImGui::Begin("Paused");
			if (ImGui::Button("Stop"))
			{
				beatmap_.stop();
			}

			if (ImGui::Button("Retry"))
			{
				// TODO: FIX THIS MESS!!!
				beatmap_.retry();
			}

			if (ImGui::Button("Resume"))
			{
				beatmap_.play();
			}

			ImGui::End();
			break;

		default:
			break;
		}

		return true;
	}

	void MainScene::end()
	{

	}

	void MainScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(beatmap_);
	}
}