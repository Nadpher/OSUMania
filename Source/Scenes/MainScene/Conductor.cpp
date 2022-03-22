#include "Conductor.h"

#include <spdlog/spdlog.h>

namespace nadpher
{
	Conductor::Conductor(const char* songPath, float offset, float bpm)
		: bpm_(bpm), crotchet_(0), offset_(offset),
		songPosition_{}
	{
		if (!song_.openFromFile(songPath))
		{
			spdlog::error("Couldn't load song {}", songPath);
		}
		else
		{
			float songDuration = song_.getDuration().asSeconds();
			crotchet_ = 60.0f / bpm_;

			spdlog::info("Song crotchet: {}", crotchet_);

			song_.setLoop(false);

			song_.play();
		}
	}

	bool Conductor::update()
	{
		// offsets for first beat
		songPosition_ = song_.getPlayingOffset().asSeconds() + offset_;

		return true;
	}
}