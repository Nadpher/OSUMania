#include "../Game.h"
#include "../TextureManager.h"

#include "Note.h"
#include "Conductor.h"
#include "Beatmap.h"

namespace nadpher
{
	Note::Note(float timePosition, float velocity, unsigned int lane)
		: timePosition_(timePosition), velocity_(velocity), lane_(lane), 
		isAlive_(true), sprite_{}
	{
		sprite_.setTexture(*TextureManager::get("Resource/Textures/notes.png"));

		sprite_.setTextureRect(sf::IntRect(lane * noteSize, 0, noteSize, noteSize));

		// centers textures on the Y axis and not on the X
		// to make it easy to center the lanes
		sprite_.setOrigin({ 0.0f, noteSize/2.0f });
		sprite_.setPosition((float)Game::getBounds().x / 2.0f + (static_cast<int>(noteSize) * (static_cast<int>(lane) - Beatmap::lanesNum / 2.0f)), 0.0f);
	}

	Note::Note(const Note& note)
		: timePosition_(note.timePosition_), velocity_(note.velocity_),
		  lane_(note.lane_), isAlive_(note.isAlive_), sprite_(note.sprite_)
	{
		
	}

	Note& Note::operator=(const Note& note)
	{
		timePosition_ = note.timePosition_;
		velocity_ = note.velocity_;
		lane_ = note.lane_;
		isAlive_ = note.isAlive_;

		sprite_ = note.sprite_;

		return *this;
	}

	Note::HitInfo Note::judge(const Conductor& conductor)
	{
		float conductorPos = conductor.getSongPosition();

		isAlive_ = false;
		if (std::abs(timePosition_ - conductorPos) < perfectTreshold)
		{
			return { perfectScore, true };
		}

		if (std::abs(timePosition_ - conductorPos) < goodTreshold)
		{
			return { goodScore, true };
		}

		if (std::abs(timePosition_ - conductorPos) < okTreshold)
		{
			return { okScore, true };
		}

		if (std::abs(timePosition_ - conductorPos) < missTreshold)
		{
			return { 0, true };
		}

		isAlive_ = true;
		return {};
	}

	bool Note::update(const Conductor& conductor)
	{
		// calculates distance to judgement line based on 
		// note velocity and song position
		sf::Vector2f worldPosition = sprite_.getPosition();

		worldPosition.y = (conductor.getSongPosition() - timePosition_)* velocity_ + (float)Game::getBounds().y - Beatmap::judgementLinePosition;
		sprite_.setPosition(worldPosition);

		// handle missed notes
		if (conductor.getSongPosition() - timePosition_ > missTreshold)
		{
			isAlive_ = false;
		}

		return isAlive_;
	}

	void Note::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite_, states);
	}
}