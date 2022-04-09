#include "../../SceneManager.h"
#include "../../Input.h"
#include "../../Game.h"
#include "../../TextureManager.h"

#include "PlayingScene.h"

#include <imgui.h>

namespace nadpher
{
	unsigned int PlayingScene::score_ = 0;

	// this is all rly cringe
	PlayingScene::PlayingScene()
		: judgementGuides_{}
	{
		sf::Vector2u gameBounds = Game::getBounds();
		for (int i = 0; i < Beatmap::lanesNum; ++i)
		{
			judgementGuides_[i].setTexture(*TextureManager::get("Resource/Textures/note-guides.png"));

			// i - 2 helps center the sprites
			judgementGuides_[i].setPosition({static_cast<float>(gameBounds.x) / 2.0f + static_cast<float>(Note::noteSize) * (i - 2), 
										     static_cast<float>(gameBounds.y) - Beatmap::judgementLinePosition});

			// centers sprite origin
			judgementGuides_[i].setOrigin({ 0.0f, static_cast<float>(Note::noteSize) / 2.0f });
			judgementGuides_[i].setTextureRect(sf::IntRect(i * Note::noteSize, 0, Note::noteSize, Note::noteSize));
		}
	}

	void PlayingScene::enter()
	{
		if (beatmap_.readFromDisk(MainScene::getPath()))
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
		popUp_.update();

		// missed notes
		Note::HitInfo info = beatmap_.update();
		if (info.hit)
		{
			popUp_.show(info.score);
		}

		// if there are no more notes to play,
		// end the song
		if (beatmap_.empty())
		{
			SceneManager::getInstance()->switchScene(SCORE_SCENE_INDEX);
			beatmap_.stop();
			return true;
		}

		if (Input::isKeyDown(sf::Keyboard::Escape))
		{
			beatmap_.pause();
		}

		handleInput();
		animateGuides();

		return true;
	}

	void PlayingScene::handleInput()
	{
		if (Input::isKeyDown(sf::Keyboard::Z))
		{
			Note::HitInfo hit = beatmap_.hitNote(0);
			score_ += hit.score;

			if (hit.hit)
			{
				popUp_.show(hit.score);
			}
		}

		if (Input::isKeyDown(sf::Keyboard::X))
		{
			Note::HitInfo hit = beatmap_.hitNote(1);
			score_ += hit.score;

			if (hit.hit)
			{
				popUp_.show(hit.score);
			}
		}

		if (Input::isKeyDown(sf::Keyboard::N))
		{
			Note::HitInfo hit = beatmap_.hitNote(2);
			score_ += hit.score;

			if (hit.hit)
			{
				popUp_.show(hit.score);
			}
		}

		if (Input::isKeyDown(sf::Keyboard::M))
		{
			Note::HitInfo hit = beatmap_.hitNote(3);
			score_ += hit.score;

			if (hit.hit)
			{
				popUp_.show(hit.score);
			}
		}
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

		ImVec2 windowSize = ImGui::GetWindowSize();
		if (ImGui::Button("Stop", ImVec2(windowSize.x, windowSize.y / 5.0f)))
		{
			beatmap_.stop();
			
			SceneManager::getInstance()->switchScene(MAIN_SCENE_INDEX);
		}

		if (ImGui::Button("Resume", ImVec2(windowSize.x, windowSize.y / 5.0f)))
		{
			beatmap_.play();
		}

		if (ImGui::Button("Retry", ImVec2(windowSize.x, windowSize.y / 5.0f)))
		{
			beatmap_.retry();
		}
		
		ImGui::EndGroup();

		ImGui::End();
	}

	void PlayingScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (int i = 0; i < Beatmap::lanesNum; ++i)
		{
			target.draw(judgementGuides_[i], states);
		}

		target.draw(beatmap_, states);

		target.draw(popUp_, states);
	}
}