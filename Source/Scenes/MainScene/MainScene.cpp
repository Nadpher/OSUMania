#include "MainScene.h"

#include "Note.h"

namespace nadpher
{
	// test
	Note note(0, 500.0f);

	bool MainScene::update()
	{
		note.update();

		return true;
	}

	void MainScene::end()
	{

	}

	void MainScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(note);
	}
}