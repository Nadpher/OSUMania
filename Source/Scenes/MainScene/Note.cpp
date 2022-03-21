#include "Note.h"

#include "../../Input.h"
#include "../../Game.h"
#include "../../TextureManager.h"

namespace nadpher
{
	Note::Note(unsigned int lane, float timePosition)
		: lane_(lane), timePosition_(timePosition),
		  worldPosition_{}, sprite_{}
	{
		sprite_.setTexture(*TextureManager::get("Resource/Textures/note.png"));
	}

	// in the future a variable will be passed as an argument
	// which will be the approach rate of the beatmap
	void Note::update()
	{
		timePosition_ += Game::getDeltaTime() * 1000.0f;
		worldPosition_.y = timePosition_;

		sprite_.setPosition(worldPosition_);
	}

	void Note::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite_);
	}
}