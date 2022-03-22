#include "../../Input.h"
#include "../../Game.h"
#include "../../TextureManager.h"

#include "Note.h"
#include "Conductor.h"
#include "MainScene.h"

namespace nadpher
{
	Note::Note(const Conductor& conductor, float timePosition, float velocity)
		: timePosition_(timePosition), velocity_(velocity),
		worldPosition_{}, sprite_{}
	{
		worldPosition_.y = (conductor.getSongPosition() - timePosition) * velocity_ + MainScene::judgementLinePosition;
		sprite_.setTexture(*TextureManager::get("Resource/Textures/note.png"));
	}

	void Note::update()
	{
		worldPosition_.y += Game::getDeltaTime() * velocity_;

		sprite_.setPosition(worldPosition_);
	}

	void Note::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite_);
	}
}