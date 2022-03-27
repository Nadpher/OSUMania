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

	unsigned int Lane::hitNote(const Conductor& conductor)
	{
		unsigned int val = judgeNote(conductor);
		if (val)
		{
			popNote();
		}
		// super bad way of fixing this bug
		else if (val == 1)
		{
			popNote();
			val--;
		}

		return val;
	}

	unsigned int Lane::judgeNote(const Conductor& conductor)
	{
		if (notes_.empty())
		{
			return 0;
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < perfectTreshold)
		{
			spdlog::info(Beatmap::perfectScore);
			return Beatmap::perfectScore;
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < goodTreshold)
		{
			spdlog::info(Beatmap::goodScore);
			return Beatmap::goodScore;
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < okTreshold)
		{
			return Beatmap::okScore;
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < missTreshold)
		{
			// sketch af
			return 1;
		}

		return 0;
	}

	void Lane::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const Note& note : notes_)
		{
			target.draw(note);
		}
	}
}