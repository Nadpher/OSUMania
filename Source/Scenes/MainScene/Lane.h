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

		void update(const Conductor& conductor);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		HitInfo hitNote(const Conductor& conductor);
		void addNote(const Note& note) { notes_.push_back(note); }

		void clear() { notes_.clear(); }

		static constexpr float missTreshold = 0.3f;
		static constexpr float okTreshold = 0.2f;
		static constexpr float goodTreshold = 0.1f;
		static constexpr float perfectTreshold = 0.05f;

	private:
		void popNote() { notes_.pop_front(); }

		void checkMisses(const Conductor& conductor);
		HitInfo judgeNote(const Conductor& conductor);

		std::deque<Note> notes_;
	};
}

#endif

