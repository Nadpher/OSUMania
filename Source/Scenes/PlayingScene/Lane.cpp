#include "Lane.h"
#include "Conductor.h"
#include "Beatmap.h"

#include <spdlog/spdlog.h>

namespace nadpher
{
	bool Lane::update(const Conductor& conductor)
	{
		bool flag = true;
		for (Note& note : notes_)
		{
			if (!note.update(conductor))
			{
				popNote();
				flag = false;
			}
		}

		return flag;
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

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < Note::perfectTreshold)
		{
			return { Beatmap::perfectScore, true };
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < Note::goodTreshold)
		{
			return { Beatmap::goodScore, true };
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < Note::okTreshold)
		{
			return { Beatmap::okScore, true };
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < Note::missTreshold)
		{
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