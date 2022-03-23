#include "../../Input.h"
#include "../../Game.h"
#include "../../TextureManager.h"

#include "Note.h"
#include "Conductor.h"
#include "MainScene.h"

namespace nadpher
{
	Note::Note(const Conductor& conductor, float timePosition, float velocity, unsigned int lane)
		: timePosition_(timePosition), velocity_(velocity), lane_(lane),
		worldPosition_{}, sprite_{}
	{
		sprite_.setTexture(*TextureManager::get("Resource/Textures/note.png"));

		worldPosition_.x = lane * sprite_.getTextureRect().width + MainScene::laneOffset;
		worldPosition_.y = (conductor.getSongPosition() - timePosition) * velocity + MainScene::judgementLinePosition;
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