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
			ImGui::SetNextWindowPos({ 0, 0 });
			ImGui::SetNextWindowSize({ 115, 120 });
			ImGui::Begin("Beatmaps", nullptr,
				ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoMove |
				ImGuiWindowFlags_NoResize |
				ImGuiWindowFlags_NoScrollbar |
			    ImGuiWindowFlags_NoTitleBar);

			if (ImGui::Button("Open", {100, 50}))
			{

			}
			if (ImGui::Button("Quit", {100, 50}))
			{
				return false;
			}
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

			ImGui::SetNextWindowPos({ 0, 0 });
			ImGui::SetNextWindowSize({ 100, 100 });
			ImGui::Begin("Paused", nullptr, 
				ImGuiWindowFlags_NoCollapse | 
				ImGuiWindowFlags_NoMove |
				ImGuiWindowFlags_NoResize |
			    ImGuiWindowFlags_NoScrollbar);

			if (ImGui::Button("Stop"))
			{
				beatmap_.stop();
			}

			if (ImGui::Button("Retry"))
			{
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