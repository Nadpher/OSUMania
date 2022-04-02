#include "../../SceneManager.h"
#include "../../Input.h"

#include "PlayingScene.h"

#include <imgui.h>

namespace nadpher
{
	PlayingScene::PlayingScene(const std::string& beatmapPath)
		: isInitialized_(false)
	{
		if (beatmapPath == "")
		{
			return;
		}

		if (beatmap_.init(beatmapPath))
		{
			isInitialized_ = true;
			beatmap_.play();
		}
	}

	bool PlayingScene::update()
	{
		if (!isInitialized_)
		{
			SceneManager::getInstance()->switchScene(MAIN_SCENE_INDEX);
			return true;
		}

		// if there are no more notes to play,
		// end the song
		if (beatmap_.empty())
		{
			SceneManager::getInstance()->switchScene(SCORE_SCENE_INDEX, "", beatmap_.getScore());
			beatmap_.stop();
			return true;
		}

		switch (beatmap_.getBeatmapStatus())
		{
		case sf::SoundSource::Stopped:
			break;

		case sf::SoundSource::Paused:
			handlePausedState();
			break;			

		case sf::SoundSource::Playing:
			beatmap_.update();

			if (Input::isKeyDown(sf::Keyboard::Escape))
			{
				beatmap_.pause();
			}

			break;

		default:
			break;
		}

		return true;
	}

	void PlayingScene::handlePausedState()
	{
		if (Input::isKeyDown(sf::Keyboard::Escape))
		{
			beatmap_.play();
		}
		ImGuiIO& io = ImGui::GetIO();
		ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x / 2.0f, io.DisplaySize.y / 2.0f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x/8.0f, io.DisplaySize.y / 6.0f));
		ImGui::Begin("Paused", nullptr, 
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse);

		ImGui::BeginGroup();

		if (ImGui::Button("Stop", ImVec2(io.DisplaySize.x / 8.0f, io.DisplaySize.y / 6.0f / 5.0f)))
		{
			beatmap_.stop();
			SceneManager::getInstance()->switchScene(MAIN_SCENE_INDEX);
		}

		if (ImGui::Button("Resume", ImVec2(io.DisplaySize.x / 8.0f, io.DisplaySize.y / 6.0f / 5.0f)))
		{
			beatmap_.play();
		}

		if (ImGui::Button("Retry", ImVec2(io.DisplaySize.x / 8.0f, io.DisplaySize.y / 6.0f / 5.0f)))
		{
			beatmap_.retry();
		}
		
		ImGui::EndGroup();

		ImGui::End();
	}

	void PlayingScene::end()
	{

	}

	void PlayingScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(beatmap_);
	}
}