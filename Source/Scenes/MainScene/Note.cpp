#include "../../Game.h"
#include "../../TextureManager.h"

#include "Note.h"
#include "Conductor.h"
#include "Beatmap.h"

namespace nadpher
{
	Note::Note(float timePosition, float velocity, unsigned int lane)
		: timePosition_(timePosition), velocity_(velocity), lane_(lane),
		worldPosition_{}, sprite_{}
	{
		sprite_.setTexture(*TextureManager::get("Resource/Textures/note.png"));

		worldPosition_.x = lane * sprite_.getTextureRect().width + Beatmap::laneOffset;
	}

	bool Note::update(const Conductor& conductor)
	{
		worldPosition_.y = (conductor.getSongPosition() - timePosition_) * velocity_ + Beatmap::judgementLinePosition;
		sprite_.setPosition(worldPosition_);

		if (conductor.getSongPosition() - timePosition_ > missTreshold)
		{
			return false;
		}

		return true;
	}

	void Note::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite_);
	}
}