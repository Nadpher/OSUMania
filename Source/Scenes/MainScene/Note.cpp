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

		auto textureSize = sprite_.getTextureRect();
		sprite_.setOrigin({ textureSize.width/2.0f, textureSize.height/2.0f });

		worldPosition_.x = lane * textureSize.width + Beatmap::laneOffset;
	}

	bool Note::update(const Conductor& conductor)
	{
		// calculates distance to judgement line based on 
		// note velocity and song position
		worldPosition_.y = (conductor.getSongPosition() - timePosition_) * velocity_ + Beatmap::judgementLinePosition;
		sprite_.setPosition(worldPosition_);

		// handle missed notes
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