#include "../../Input.h"
#include "../../Game.h"
#include "../../TextureManager.h"

#include "Note.h"
#include "Conductor.h"

namespace nadpher
{
	Note::Note(unsigned int lane, float timePosition)
		: lane_(lane), worldPosition_{}, sprite_{}
	{
		sprite_.setTexture(*TextureManager::get("Resource/Textures/note.png"));
	}

	void Note::update(Conductor& conductor)
	{
		worldPosition_.x = conductor.getSongPosition();

		sprite_.setPosition(worldPosition_);
	}

	void Note::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite_);
	}
}