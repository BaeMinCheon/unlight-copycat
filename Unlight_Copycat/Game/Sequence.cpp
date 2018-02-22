#include "Sequence.h"
#include "GameWindow.h"

void Sequence::leftClick(int x, int y)
{
	++GameWindow::sequenceIndex;
	if (GameWindow::sequenceIndex == GameWindow::sequenceVector.size())
	{
		GameWindow::sequenceIndex = 0;
	}
}

void Sequence::doubleClick(int x, int y)
{
	;
}

void Sequence::rightClick(int x, int y)
{
	;
}

// ===============================================================

Main::Main()
{
	init();
}

void Main::init()
{
	;
}

void Main::draw(Application& app)
{
	app.wout << setpos(10, 10) << TEXT("Main Sequence");
}

void Main::leftClick(int x, int y)
{
	Sequence::leftClick(x, y);
}

void Main::doubleClick(int x, int y)
{
	;
}

void Main::rightClick(int x, int y)
{
	;
}

// ===============================================================

Quest::Quest()
{
	init();
}

void Quest::init()
{
	;
}

void Quest::draw(Application& app)
{
	app.wout << setpos(10, 10) << TEXT("Quest Sequence");
}

void Quest::leftClick(int x, int y)
{
	Sequence::leftClick(x, y);
}

void Quest::doubleClick(int x, int y)
{
	;
}

void Quest::rightClick(int x, int y)
{
	;
}

// ===============================================================

Battle::Battle()
{
	init();
}

void Battle::init()
{
	;
}

void Battle::draw(Application& app)
{
	app.wout << setpos(10, 10) << TEXT("Battle Sequence");
}

void Battle::leftClick(int x, int y)
{
	Sequence::leftClick(x, y);
}

void Battle::doubleClick(int x, int y)
{
	;
}

void Battle::rightClick(int x, int y)
{
	;
}

// ===============================================================