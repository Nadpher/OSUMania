#ifndef OSUMANIA_BEATMAP_H
#define OSUMANIA_BEATMAP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <array>
#include <vector>

#include "Conductor.h"
#include "Note.h"

namespace nadpher
{
	class Beatmap : public sf::Drawable
	{
	public:
		Beatmap();

		sf::SoundSource::Status getBeatmapStatus() const { return song_.getStatus(); }

		Note::HitInfo update();
		Note::HitInfo hitNote(unsigned int lane);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		bool readFromDisk(const std::string& folderPath);
		// bool writeToDisk();

		bool empty();

		void retry()
		{
			stop();

			conductor_.reset();

			for (Note& note : notes_)
			{
				note.revive();
			}

			play();
		}

		void play()  { song_.play();  }
		void pause() { song_.pause(); }
		void stop()  { song_.stop();  }

		static constexpr unsigned int lanesNum = 4;

		static constexpr float judgementLinePosition = 200.0f;

	private:
	friend class EditScene;

		void loadTimePositions();

		std::vector<Note> notes_;

		std::string fileString_;

		// should probably move this to conductor
		sf::Music song_;

		Conductor conductor_;
	};
}

#endif
