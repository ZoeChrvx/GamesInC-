#include <SDL.h>
#include "Game.h"

int main(int argc, char** argv)
{
	bool isGameInit = Game::instance().Initialize();
	if (isGameInit) {
		Game::instance().Loop();
	}
	Game::instance().Close();
	return 0;
}