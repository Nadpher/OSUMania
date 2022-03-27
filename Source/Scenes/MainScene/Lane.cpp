#include "Lane.h"
#include "Conductor.h"
#include "Beatmap.h"

#include <spdlog/spdlog.h>

namespace nadpher
{
	void Lane::update(const Conductor& conductor)
	{
		for (Note& note : notes_)
		{
			note.update(conductor);
		}

		checkMisses(conductor);
	}

	void Lane::checkMisses(const Conductor& conductor)
	{
		if (notes_.empty())
		{
			return;
		}

		// miss treshold is divided by 5 to make asymmetrical timings between 
		// early hits and late hits. ill just keep it a magic constant for now
		// since this is the only place where it's being used.
		if (conductor.getSongPosition() - notes_.front().getTimePosition() > missTreshold / 5.0f)
		{
			spdlog::info("Missed");
			popNote();
		}
	}

	Lane::HitInfo Lane::hitNote(const Conductor& conductor)
	{
		HitInfo val = judgeNote(conductor);
		if (val.hit)
		{
			popNote();
		}

		return val;
	}

	Lane::HitInfo Lane::judgeNote(const Conductor& conductor)
	{
		if (notes_.empty())
		{
			return { 0, false };
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < perfectTreshold)
		{
			spdlog::info(Beatmap::perfectScore);
			return { Beatmap::perfectScore, true };
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < goodTreshold)
		{
			spdlog::info(Beatmap::goodScore);
			return { Beatmap::goodScore, true };
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < okTreshold)
		{
			return { Beatmap::okScore, true };
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < missTreshold)
		{
			// sketch af
			return { 0, true };
		}

		return { 0, false };
	}

	void Lane::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const Note& note : notes_)
		{
			target.draw(note);
		}
	}
}