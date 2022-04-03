#include "../../SceneManager.h"
#include "../../Input.h"
#include "../../Game.h"
#include "../../TextureManager.h"

#include "PlayingScene.h"

#include <imgui.h>

namespace nadpher
{
	// this is all rly cringe
	PlayingScene::PlayingScene(const std::string& beatmapPath)
		: isInitialized_(false), cooldownTimer_(0.0f), 
		  judgementGuides_{}
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

		sf::Vector2u gameBounds = Game::getBounds();
		for (int i = 0; i < Beatmap::lanesNum; ++i)
		{
			judgementGuides_[i].setTexture(*TextureManager::get("Resource/Textures/note-guides.png"));

			// i - 2 helps center the sprites
			// 128 is the size of the sprite
			judgementGuides_[i].setPosition({static_cast<float>(gameBounds.x) / 2.0f + static_cast<float>(Note::noteSize) * (i - 2), 
										     static_cast<float>(gameBounds.y) - Beatmap::judgementLinePosition});

			// centers sprite origin
			judgementGuides_[i].setOrigin({ 0.0f, static_cast<float>(Note::noteSize) / 2.0f });

			judgementGuides_[i].setTextureRect(sf::IntRect(i * Note::noteSize, 0, Note::noteSize, Note::noteSize));
		}
	}

	bool PlayingScene::update()
	{
		if (!isInitialized_)
		{
			SceneManager::getInstance()->switchScene(MAIN_SCENE_INDEX);
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
			handlePlayingState();
			break;

		default:
			break;
		}

		return true;
	}

	bool PlayingScene::handlePlayingState()
	{
		beatmap_.update();

		// if there are no more notes to play,
		// wait cooldownTime and end the song
		if (beatmap_.empty())
		{
			if (cooldownTimer_ > cooldownTime)
			{
				SceneManager::getInstance()->switchScene(SCORE_SCENE_INDEX, "", beatmap_.getScore());
				beatmap_.stop();
				return true;
			}

			cooldownTimer_ += Game::getDeltaTime();
		}

		if (Input::isKeyDown(sf::Keyboard::Escape))
		{
			beatmap_.pause();
		}

		animateGuides();

		return true;
	}

	void PlayingScene::animateGuides()
	{
		if (Input::isKeyDown(sf::Keyboard::Z) || Input::isKeyUp(sf::Keyboard::Z))
		{
			sf::IntRect rect = judgementGuides_[0].getTextureRect();
			rect.top = std::abs(rect.top - static_cast<int>(Note::noteSize));

			judgementGuides_[0].setTextureRect(rect);
		}

		if (Input::isKeyDown(sf::Keyboard::X) || Input::isKeyUp(sf::Keyboard::X))
		{
			sf::IntRect rect = judgementGuides_[1].getTextureRect();
			rect.top = std::abs(rect.top - static_cast<int>(Note::noteSize));

			judgementGuides_[1].setTextureRect(rect);
		}

		if (Input::isKeyDown(sf::Keyboard::N) || Input::isKeyUp(sf::Keyboard::N))
		{
			sf::IntRect rect = judgementGuides_[2].getTextureRect();
			rect.top = std::abs(rect.top - static_cast<int>(Note::noteSize));

			judgementGuides_[2].setTextureRect(rect);
		}

		if (Input::isKeyDown(sf::Keyboard::M) || Input::isKeyUp(sf::Keyboard::M))
		{
			sf::IntRect rect = judgementGuides_[3].getTextureRect();
			rect.top = std::abs(rect.top - static_cast<int>(Note::noteSize));

			judgementGuides_[3].setTextureRect(rect);
		}

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
		for (int i = 0; i < Beatmap::lanesNum; ++i)
		{
			target.draw(judgementGuides_[i]);
		}

		target.draw(beatmap_);
	}
}