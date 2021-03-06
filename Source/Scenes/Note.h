#ifndef OSUMANIA_NOTE_H
#define OSUMANIA_NOTE_H

#include <SFML/Graphics.hpp>

namespace nadpher
{
	class Conductor;

	class Note : public sf::Drawable
	{
	public:
		Note(float timePosition = 0.0f, float velocity = 1.0f, unsigned int lane = 0);
		Note(const Note& note);
		~Note() = default;

		Note& operator=(const Note& note);

		struct HitInfo
		{
			unsigned int score;
			bool hit;
		};

		bool update(const Conductor& conductor);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void revive() { isAlive_ = true; }

		float getTimePosition() const { return timePosition_; }
		float getVelocity() const { return velocity_; }
		unsigned int getLane() const { return lane_; }

		bool isAlive() const { return isAlive_; }

		HitInfo judge(const Conductor& conductor);

		static constexpr unsigned int okScore = 50;
		static constexpr unsigned int goodScore = 100;
		static constexpr unsigned int perfectScore = 300;

		static constexpr float missTreshold = 0.1f;
		static constexpr float okTreshold = 0.075f;
		static constexpr float goodTreshold = 0.050f;
		static constexpr float perfectTreshold = 0.025f;

		static constexpr unsigned int noteSize = 128;

	private:

		bool isAlive_;

		unsigned int lane_;

		float timePosition_;
		float velocity_;

		sf::Sprite sprite_;
	};
}

#endif

