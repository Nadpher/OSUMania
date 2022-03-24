#ifndef OSUMANIA_LANE_H
#define OSUMANIA_LANE_H

#include <deque>

#include "Note.h"

namespace nadpher
{
	class Lane : public sf::Drawable
	{
	public:

		void update();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void addNote(const Note& note) { notes_.push_back(note); }
		bool judgeNote(const Conductor& conductor);

		void popNote() { notes_.pop_front(); }
		void clear() { notes_.clear(); }

		static constexpr float missTreshold = 0.3f;
		static constexpr float okTreshold = 0.2f;
		static constexpr float goodTreshold = 0.1f;
		static constexpr float perfectTreshold = 0.05f;

	private:
		std::deque<Note> notes_;
	};
}

#endif

