#include "Conductor.h"

#include <spdlog/spdlog.h>

namespace nadpher
{
	Conductor::Conductor()
		: bpm_(0), crotchet_(0), offset_(0),
		songPosition_(0.0f)
	{
	}

	void Conductor::init(float offset, float bpm)
	{
		offset_ = offset;
		bpm_ = bpm;

		crotchet_ = 60.0f / bpm;
		spdlog::info("Song crotchet = {}", crotchet_);
	}

	bool Conductor::update(float songPosition)
	{
		// offsets for first beat
		songPosition_ = songPosition + offset_;

		return true;
	}
}