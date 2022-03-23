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

	}

	bool MainScene::update()
	{

		ImGui::Begin("Test");
		ImGui::Button("Test button");
		ImGui::End();

		return true;
	}

	void MainScene::end()
	{

	}

	void MainScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// target.draw(beatmap_);
	}
}