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
			break;

		default:
			ImGui::Begin("Paused");
			if (ImGui::Button("Stop"))
			{
				beatmap_.stop();
			}

			if (ImGui::Button("Resume"))
			{
				beatmap_.pause();
			}

			ImGui::End();
			break;
		}

		if (Input::isKeyDown(sf::Keyboard::Key::Escape))
		{
			beatmap_.pause();
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