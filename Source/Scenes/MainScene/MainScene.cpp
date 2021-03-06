#include "../../Game.h"
#include "../../SceneManager.h"

#include "MainScene.h"

#include <spdlog/spdlog.h>
#include <imgui.h>

// because i clearly didn't have enough dependencies already -.-
#include <nfd.h>

namespace nadpher
{
	std::string MainScene::selectedMapPath_;

	void MainScene::enter()
	{

	}

	bool MainScene::update()
	{
		return drawGui();
	}

	bool MainScene::drawGui()
	{
		ImGuiIO& io = ImGui::GetIO();
		const float padding = 10.0f;

		ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x / 2.0f, io.DisplaySize.y / 2.0f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowSize({ io.DisplaySize.x / 4.0f, io.DisplaySize.y / 4.0f });
		ImGui::Begin("Beatmaps", nullptr,
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoScrollWithMouse);

		ImVec2 windowSize = ImGui::GetWindowSize();

		ImGui::BeginGroup();
		ImGui::SetCursorPosX(padding);
		if (ImGui::Button("Play", { windowSize.x - padding * 2.0f, windowSize.y / 3.0f - padding }))
		{
			selectedMapPath_ = openBeatmap();
			SceneManager::getInstance()->switchScene(PLAYING_SCENE_INDEX);
		}

		ImGui::SetCursorPosX(padding);
		if (ImGui::Button("Edit", { windowSize.x - padding * 2.0f, windowSize.y / 3.0f - padding }))
		{
			selectedMapPath_ = openBeatmap();
			SceneManager::getInstance()->switchScene(EDIT_SCENE_INDEX);
		}

		ImGui::SetCursorPosX(padding);
		if (ImGui::Button("Quit", { windowSize.x - padding * 2.0f, windowSize.y / 3.0f - padding }))
		{
			return false;
		}
		ImGui::EndGroup();

		ImGui::End();

		return true;
	}

	std::string MainScene::openBeatmap()
	{
		// sketchy C mem allocation

		// this stops deltatime calculation ............
		nfdchar_t* outPath = nullptr;
		nfdresult_t result = NFD_PickFolder(NULL, &outPath);
		if (result == NFD_OKAY)
		{
			spdlog::info("Selected beatmap folder: {}", outPath);

			std::string path(outPath);
			path += '/';
			free(outPath);

			return path;
		}
		else if (result != NFD_CANCEL)
		{
			spdlog::error(NFD_GetError());
		}

		return "";
	}

	void MainScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

	}
}