#include "Lane.h"
#include "Conductor.h"

#include <spdlog/spdlog.h>

namespace nadpher
{
	bool Lane::update(const Conductor& conductor)
	{
		bool flag = false;
		for (Note& note : notes_)
		{
			if (!note.update(conductor))
			{
				popNote();
				flag = true;
			}
		}

		return flag;
	}

	Note::HitInfo Lane::hitNote(const Conductor& conductor)
	{
		Note::HitInfo val = judgeNote(conductor);
		if (val.hit)
		{
			popNote();
		}

		return val;
	}

	Note::HitInfo Lane::judgeNote(const Conductor& conductor)
	{
		if (notes_.empty())
		{
			return { 0, false };
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < Note::perfectTreshold)
		{
			return { Note::perfectScore, true };
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < Note::goodTreshold)
		{
			return { Note::goodScore, true };
		}

		if (std::abs(notes_.front().getTimePosition() - conductor.getSongPosition()) < Note::okTreshold)
		{
			return { Note::okScore, true };
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