#ifndef OSUMANIA_CONDUCTOR_H
#define OSUMANIA_CONDUCTOR_H

#include <SFML/Audio.hpp>

// todo: work out how this is supposed to work
namespace nadpher
{
	class Conductor
	{
	public:
		Conductor(const char* songPath, float offset, float bpm = 120.0f);

		float getSongPosition() const { return songPosition_; }
		float getCrotchet() const { return crotchet_; }
		float getBPM() const { return bpm_; }

		bool update();

	private:

		sf::Music song_;

		float offset_;
		float bpm_;
		float crotchet_;
		float songPosition_;
	};
}

#endif

