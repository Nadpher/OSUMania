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

		struct HitInfo
		{
			unsigned int score;
			bool hit;
		};

		bool update(const Conductor& conductor);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		float getTimePosition() const { return timePosition_; }
		unsigned int getLane() const { return lane_; }

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

		const unsigned int lane_;

		const float timePosition_;
		const float velocity_;

		sf::Vector2f worldPosition_;
		sf::Sprite sprite_;
	};
}

#endif

