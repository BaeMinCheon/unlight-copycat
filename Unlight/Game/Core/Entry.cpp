#include <iostream>
#include <Core/Game.h>

int mainLAF()
{
	Game app = Game(TEXT("Unlight"), 800, 800, 100, 100);
	app.run();

	return 0;
}