#include "../../Input.h"
#include "../../Game.h"
#include "../../TextureManager.h"

#include "Note.h"
#include "Conductor.h"

namespace nadpher
{
	Note::Note(unsigned int lane, float timePosition, float speed)
		: lane_(lane), timePosition_(timePosition), speed_(speed),
		  worldPosition_{}, sprite_{}
	{
		sprite_.setTexture(*TextureManager::get("Resource/Textures/note.png"));
		worldPosition_.y = -speed_ * timePosition_;
	}

	void Note::update(Conductor& conductor)
	{
		worldPosition_.y += speed_ * Game::getDeltaTime();

		sprite_.setPosition(worldPosition_);
	}

	void Note::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite_);
	}
}