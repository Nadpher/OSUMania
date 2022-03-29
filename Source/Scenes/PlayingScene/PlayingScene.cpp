#include "../../SceneManager.h"
#include "../../Input.h"

#include "PlayingScene.h"

#include <imgui.h>

namespace nadpher
{
	PlayingScene::PlayingScene(const char* beatmapPath)
	{
		if (beatmapPath == "")
		{
			return;
		}

		if (beatmap_.init(beatmapPath))
		{
			beatmap_.play();
		}
		else
		{
			SceneManager::getInstance()->switchScene(MAIN_SCENE_INDEX);
		}
	}

	bool PlayingScene::update()
	{
		switch (beatmap_.getBeatmapStatus())
		{
		case sf::SoundSource::Stopped:
			SceneManager::getInstance()->switchScene(MAIN_SCENE_INDEX);
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
		ImGui::Begin("Paused");

		ImGui::BeginGroup();

		if (ImGui::Button("Stop"))
		{
			beatmap_.stop();
		}

		if (ImGui::Button("Resume"))
		{
			beatmap_.play();
		}

		if (ImGui::Button("Retry"))
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