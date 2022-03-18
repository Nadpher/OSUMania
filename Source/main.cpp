#include "Game.h"

int main()
{
	// this never fails, idk why im even coding this check in
	if (!nadpher::Game::init(1024, 768))
	{
		return 1;
	}
	nadpher::Game::run();
}