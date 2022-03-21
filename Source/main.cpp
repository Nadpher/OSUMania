#include "Game.h"

int main()
{
	if (!nadpher::Game::init(1024, 768))
	{
		return 1;
	}
	nadpher::Game::run();

	return 0;
}