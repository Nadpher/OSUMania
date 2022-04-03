#ifndef OSUMANIA_BEATMAP_H
#define OSUMANIA_BEATMAP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <array>

#include "Conductor.h"
#include "Lane.h"

namespace nadpher
{
	class Beatmap : public sf::Drawable
	{
	public:
		Beatmap();

		sf::SoundSource::Status getBeatmapStatus() const { return song_.getStatus(); }

		Note::HitInfo update();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		unsigned int getScore() const { return score_; }

		bool init(const std::string& folderPath);
		bool empty()
		{
			for (const Lane& lane : lanes_)
			{
				if (!lane.empty())
				{
					return false;
				}
			}

			return true;
		}

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
			score_ = 0;
			song_.stop();

			clearLanes();
		}

		static constexpr unsigned int lanesNum = 4;

		static constexpr float judgementLinePosition = 200.0f;

	private:

		unsigned int score_;

		void clearLanes();
		void loadTimePositions();

		std::string fileString_;
		std::array<Lane, lanesNum> lanes_;

		// should probably move this to conductor
		sf::Music song_;

		Conductor conductor_;
	};
}

#endif
