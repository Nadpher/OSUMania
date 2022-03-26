#include "Lane.h"
#include "Conductor.h"

#include <spdlog/spdlog.h>

namespace nadpher
{
	void Lane::update(const Conductor& conductor)
	{
		for (Note& note : notes_)
		{
			note.update();
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

	void Lane::hitNote(const Conductor& conductor)
	{
		if (judgeNote(conductor))
		{
			popNote();
		}
	}

	bool Lane::judgeNote(const Conductor& conductor)
	{
		if (notes_.empty())
		{
			return false;
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < perfectTreshold)
		{
			spdlog::info("Perfect");
			return true;
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < goodTreshold)
		{
			spdlog::info("Good");
			return true;
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < okTreshold)
		{
			spdlog::info("Ok");
			return true;
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < missTreshold)
		{
			spdlog::info("Miss");
			return true;
		}

		return false;
	}

	void Lane::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const Note& note : notes_)
		{
			target.draw(note);
		}
	}
}