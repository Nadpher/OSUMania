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
			ImGui::Begin("Test");
			ImGui::Button("Test button");
			ImGui::End();
			break;

		case sf::SoundSource::Playing:
			beatmap_.update();
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