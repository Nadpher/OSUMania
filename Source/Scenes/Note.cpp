#include "../Game.h"
#include "../TextureManager.h"

#include "Note.h"
#include "Conductor.h"
#include "Beatmap.h"

namespace nadpher
{
	Note::Note(float timePosition, float velocity, unsigned int lane)
		: timePosition_(timePosition), velocity_(velocity), lane_(lane),
		worldPosition_{}, sprite_{}
	{
		sprite_.setTexture(*TextureManager::get("Resource/Textures/notes.png"));

		// 128 is the size of each arrow
		sprite_.setTextureRect(sf::IntRect(lane * 128, 0, 128, 128));

		// centers textures on the Y axis and not on the X
		// to make it easy to center the lanes
		auto textureSize = sprite_.getTextureRect();
		sprite_.setOrigin({ 0.0f, textureSize.height/2.0f });

		// im using -2 to split the 4 lanes into two where the first two lanes
		// will be -2 and -1 and the next two will be 0 and 1, centering the sprites
		worldPosition_.x = Game::getBounds().x / 2.0f + (textureSize.width * (static_cast<int>(lane) - 2));
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
		worldPosition_.y = (conductor.getSongPosition() - timePosition_) * velocity_ + (float)Game::getBounds().y - Beatmap::judgementLinePosition;
		sprite_.setPosition(worldPosition_);

		// handle missed notes
		if (conductor.getSongPosition() - timePosition_ > missTreshold)
		{
			isAlive_ = false;
		}

		return isAlive_;
	}

	void Note::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite_);
	}
}