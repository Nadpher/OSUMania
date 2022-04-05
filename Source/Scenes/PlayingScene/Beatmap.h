#ifndef OSUMANIA_BEATMAP_H
#define OSUMANIA_BEATMAP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <array>
#include <deque>

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
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		bool readFromDisk(const std::string& folderPath);
		Note::HitInfo hitNote(unsigned int lane);
		// bool writeToDisk();

		bool empty() const { return notes_.empty(); }

		void retry()
		{
			stop();
			conductor_.reset();

			loadTimePositions();
			play();
		}

		void play()  { song_.play();  }
		void pause() { song_.pause(); }

		void stop()  
		{
			song_.stop();

			notes_.clear();
		}

		static constexpr unsigned int lanesNum = 4;

		static constexpr float judgementLinePosition = 200.0f;

	private:

		void loadTimePositions();

		std::deque<Note> notes_;

		std::string fileString_;

		// should probably move this to conductor
		sf::Music song_;

		Conductor conductor_;
	};
}

#endif
