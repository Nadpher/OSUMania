#ifndef OSUMANIA_CONDUCTOR_H
#define OSUMANIA_CONDUCTOR_H

#include <SFML/Audio.hpp>

namespace nadpher
{
	class Conductor
	{
	public:
		Conductor(const char* songPath, float bpm = 120.0f);

		float getSongPosition() const { return songPosition_; }
		float getBPM() const { return bpm_; }

		bool update();

	private:

		sf::Music song_;

		float bpm_;
		float crotchet_;
		float songPosition_;
	};
}

#endif

