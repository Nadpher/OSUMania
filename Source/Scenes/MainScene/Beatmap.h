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

		void update();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		bool init(const std::string& folderPath);

		void play()  { song_.play();  }

		void pause()
		{
			if (song_.getStatus() == sf::SoundSource::Paused)
			{
				song_.play();
			}
			else
			{
				song_.pause();
			}
 	    }

		void stop()  { song_.stop();  }

		static constexpr unsigned int lanesNum = 4;

		static constexpr float laneOffset = 350.0f;
		static constexpr float judgementLinePosition = 500.0f;

	private:

		sf::VertexArray judgementLine_;
		std::array<Lane, lanesNum> lanes_;
		sf::Music song_;
		Conductor conductor_;
	};
}

#endif
