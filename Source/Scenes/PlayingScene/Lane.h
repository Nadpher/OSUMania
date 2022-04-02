#ifndef OSUMANIA_LANE_H
#define OSUMANIA_LANE_H

#include <deque>

#include "Note.h"

namespace nadpher
{
	class Lane : public sf::Drawable
	{
	public:

		struct HitInfo
		{
			unsigned int score;
			bool hit;
		};

		bool update(const Conductor& conductor);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		HitInfo hitNote(const Conductor& conductor);
		void addNote(const Note& note) { notes_.push_back(note); }

		bool empty() const { return notes_.empty(); }
		void clear() { notes_.clear(); }

	private:

		void popNote() { notes_.pop_front(); }

		HitInfo judgeNote(const Conductor& conductor);

		std::deque<Note> notes_;
	};
}

#endif

