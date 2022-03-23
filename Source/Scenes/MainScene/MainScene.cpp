#include "../../Game.h"
#include "../../Input.h"
#include "../../TextureManager.h"

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
			break;

		case sf::SoundSource::Playing:
			beatmap_.update();
			break;

		default:
			ImGui::Begin("Paused");
			ImGui::Button("Stop");
			ImGui::End();
			break;
		}

		if (Input::isKeyPressed(sf::Keyboard::Key::Escape))
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