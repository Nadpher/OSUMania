#include "Conductor.h"

#include <spdlog/spdlog.h>

namespace nadpher
{
	Conductor::Conductor(const char* songPath, float bpm)
		: bpm_(bpm), crotchet_(0), songPosition_(0)
	{
		if (!song_.openFromFile(songPath))
		{
			spdlog::error("Couldn't load song {}", songPath);
		}
		else
		{
			float songDuration = song_.getDuration().asSeconds();
			crotchet_ = songDuration / bpm_;

			spdlog::info("Song crotchet: {}", crotchet_);

			song_.setLoop(false);

			song_.play();
		}
	}

	bool Conductor::update()
	{
		songPosition_ = song_.getPlayingOffset().asSeconds();

		return true;
	}
}