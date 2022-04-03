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

		bool update(const Conductor& conductor);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		const float getTimePosition() const { return timePosition_; }

		static constexpr float missTreshold = 0.1f;
		static constexpr float okTreshold = 0.075f;
		static constexpr float goodTreshold = 0.050f;
		static constexpr float perfectTreshold = 0.025f;

		static constexpr unsigned int noteSize = 128;

	private:

		const size_t lane_;

		const float timePosition_;
		const float velocity_;

		sf::Vector2f worldPosition_;
		sf::Sprite sprite_;
	};
}

#endif

