#include "Lane.h"
#include "Conductor.h"

#include <spdlog/spdlog.h>

namespace nadpher
{
	void Lane::update()
	{
		for (Note& note : notes_)
		{
			note.update();
		}
	}

	bool Lane::judgeNote(const Conductor& conductor)
	{
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