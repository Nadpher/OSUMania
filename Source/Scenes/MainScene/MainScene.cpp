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
		case sf::SoundSource::Stopped:
			if (!handleStoppedState())
			{
				return false;
			}
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

	bool MainScene::handleStoppedState()
	{
		sf::Vector2u windowsize = Game::getBounds();

		ImGui::SetNextWindowPos(ImVec2(windowsize.x / 2.0f, windowsize.y / 2.0f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowSize({ windowsize.x / 10.0f, windowsize.y / 8.0f });
		ImGui::Begin("Beatmaps", nullptr,
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoTitleBar);

		ImGui::SetCursorPos(ImVec2(0.0f, 0.0f));
		ImGui::BeginGroup();
		if (ImGui::Button("Open", { windowsize.x / 10.0f, windowsize.y / 16.0f}))
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
		if (ImGui::Button("Quit", { windowsize.x / 10.0f, windowsize.y/16.0f}))
		{
			return false;
		}
		ImGui::EndGroup();	

		ImGui::End();

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