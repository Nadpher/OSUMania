#include "../../Input.h"
#include "../../SceneManager.h"
#include "../../Game.h"
#include "../../TextureManager.h"

#include "EditScene.h"

#include "../MainScene/MainScene.h"

#include <spdlog/spdlog.h>
#include <imgui.h>

namespace nadpher
{
	EditScene::EditScene()
		: changed_(false)
	{
		sf::Vector2u gameBounds = Game::getBounds();
		for (int i = 0; i < Beatmap::lanesNum; ++i)
		{
			judgementGuides_[i].setTexture(*TextureManager::get("Resource/Textures/note-guides.png"));

			// i - 2 helps center the sprites
			judgementGuides_[i].setPosition({ static_cast<float>(gameBounds.x) / 2.0f + static_cast<float>(Note::noteSize) * (i - 2),
											 static_cast<float>(gameBounds.y) - Beatmap::judgementLinePosition });

			// centers sprite origin
			judgementGuides_[i].setOrigin({ 0.0f, static_cast<float>(Note::noteSize) / 2.0f });
			judgementGuides_[i].setTextureRect(sf::IntRect(i * Note::noteSize, 0, Note::noteSize, Note::noteSize));
		}
	}

	void EditScene::enter()
	{
		std::string path = MainScene::getPath();
		if (!beatmap_.readFromDisk(path))
		{
			SceneManager::getInstance()->switchScene(MAIN_SCENE_INDEX);
		}
	}

	bool EditScene::update()
	{
		beatmap_.update();

		switch (beatmap_.getBeatmapStatus())
		{
		case sf::SoundSource::Paused:
		case sf::SoundSource::Stopped:
			handleStoppedState();
			break;

		case sf::SoundSource::Playing:
			autoHit();

			if (Input::isKeyDown(sf::Keyboard::Space))
			{
				beatmap_.pause();
			}
			break;

		default:
			break;
		}

		return true;
	}

	void EditScene::handleStoppedState()
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, 0.0f));
		if (ImGui::Begin("Timeline", 0,
			ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoCollapse))
		{
			float songPosition = beatmap_.conductor_.getSongPosition() - beatmap_.conductor_.getOffset();
			if (ImGui::SliderFloat("Pos", & songPosition, 0.0f, beatmap_.song_.getDuration().asSeconds(), "%.2f", ImGuiSliderFlags_AlwaysClamp))
			{
				beatmap_.song_.setPlayingOffset(sf::Time(sf::seconds(songPosition)));
				reloadPositions();
			}
		}
		ImGui::End();

		if (ImGui::Begin("Edit..."))
		{
			if (ImGui::Button("Save") && changed_)
			{
				changed_ = false;
				// beatmap_.writeToDisk();
			}

		}
		ImGui::End();

		if (Input::isKeyDown(sf::Keyboard::Space))
		{
			beatmap_.play();
		}
	}

	void EditScene::reloadPositions()
	{
		float songPosition = beatmap_.song_.getPlayingOffset().asSeconds() + beatmap_.conductor_.getOffset();
		for (Note& note : beatmap_.notes_)
		{
			if (note.getTimePosition() >= songPosition)
			{
				note.revive();
			}
		}
	}

	void EditScene::autoHit()
	{
		size_t len = beatmap_.notes_.size();
		for (int i = 0; i < len; ++i)
		{
			if (beatmap_.notes_[i].getTimePosition() <= beatmap_.conductor_.getSongPosition())
			{
				beatmap_.hitNote(beatmap_.notes_[i].getLane());
			}
			else
			{
				break;
			}
		}
	}

	void EditScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const sf::Sprite& sprite : judgementGuides_)
		{
			target.draw(sprite, states);
		}
		target.draw(beatmap_, states);
	}
}