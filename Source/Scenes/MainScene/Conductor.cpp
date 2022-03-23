#include "Conductor.h"

#include <spdlog/spdlog.h>

namespace nadpher
{
	Conductor::Conductor(float duration, float offset, float bpm)
		: bpm_(bpm), crotchet_(0), offset_(offset),
		songPosition_{}
	{
		crotchet_ = 60.0f / bpm_;
		spdlog::info("Song crotchet: {}", crotchet_);
	}

	bool Conductor::update(float songPosition)
	{
		// offsets for first beat
		songPosition_ = songPosition + offset_;

		return true;
	}
}