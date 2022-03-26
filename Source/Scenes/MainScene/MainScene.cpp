#include "../../Game.h"
#include "../../TextureManager.h"
#include "../../Input.h"

#include "MainScene.h"
#include "Note.h"

#include <spdlog/spdlog.h>
#include <imgui.h>

// because i clearly didn't have enough dependencies already -.-
#include <nfd.h>

namespace nadpher
{
	MainScene::MainScene()
	{
		sf::Vector2u bounds = Game::getBounds();
	}

	bool MainScene::update()
	{
		switch (beatmap_.getBeatmapStatus())
		{
		// didn't transfer this state to a diff function cause
		// i need it to return false when quit is pressed
		// and i cba to make another bool func
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
				// sketchy C mem allocation

				// this stops deltatime calculation ............
				nfdchar_t* outPath = nullptr;
				nfdresult_t result = NFD_PickFolder(NULL, &outPath);
				if (result == NFD_OKAY)
				{
					spdlog::info("Selected beatmap folder: {}", outPath);
					if (beatmap_.init(outPath))
					{
						beatmap_.play();
					}

					free(outPath);
				}
				else if (result != NFD_CANCEL)
				{
					spdlog::error(NFD_GetError());
				}
			}
			if (ImGui::Button("Quit", {100, 50}))
			{
				return false;
			}
			ImGui::End();
			break;

		case sf::SoundSource::Playing:
			handlePlayingState();
			break;

		case sf::SoundSource::Paused:
			handlePausedState();
			break;

		default:
			break;
		}

		return true;
	}

	void MainScene::handlePlayingState()
	{
		beatmap_.update();

		if (Input::isKeyDown(sf::Keyboard::Key::Escape))
		{
			beatmap_.pause();
		}
	}

	void MainScene::handlePausedState()
	{
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
	}

	void MainScene::end()
	{
		
	}

	void MainScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(beatmap_);
	}
}