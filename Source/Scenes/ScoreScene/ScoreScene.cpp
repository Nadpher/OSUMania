#include "ScoreScene.h"

#include "../../Game.h"
#include "../../FontManager.h"
#include "../../SceneManager.h"

#include "../PlayingScene/PlayingScene.h"

#include <imgui.h>

namespace nadpher
{
	ScoreScene::ScoreScene()
	{
		scoreText_.setFont(*FontManager::get("Resource/Fonts/regularFont.ttf"));
	}

	void ScoreScene::enter()
	{
		std::string scoreString("Score: ");
		scoreString += std::to_string(PlayingScene::getScore());

		scoreText_.setString(scoreString);

		scoreText_.setCharacterSize(64);

		// center text
		scoreText_.setPosition({ (float)Game::getBounds().x / 2.0f, (float)Game::getBounds().y / 2.0f });
		sf::FloatRect rect = scoreText_.getLocalBounds();
		scoreText_.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
	}

	bool ScoreScene::update()
	{
		// draw gui
		ImGuiIO& io = ImGui::GetIO();

		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
		ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x / 4.0f, io.DisplaySize.y / 4.0f));
		ImGui::Begin("help", nullptr,
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoTitleBar);

		ImVec2 windowSize = ImGui::GetWindowSize();
		if (ImGui::Button("Back", ImVec2(windowSize.x, windowSize.y / 2.0f)))
		{
			SceneManager::getInstance()->switchScene(MAIN_SCENE_INDEX);
		}

		ImGui::End();

		return true;
	}

	void ScoreScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(scoreText_, states);
	}
}