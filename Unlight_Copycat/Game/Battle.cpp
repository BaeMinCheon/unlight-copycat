#include "Battle.h"
#include "GameWindow.h"

Battle::Battle()
{
	init();
}

void Battle::init()
{
	buttonVector.push_back(std::make_shared<RectButton>(10, 10, 60, 30,
		(TCHAR*)TEXT("Back"), white, []()
	{
		GameWindow::currentSequence = "Quest";
	}));
}

void Battle::draw(Application& app)
{
	app.wout << setpos(100, 15) << TEXT("Battle Sequence");

	for (auto b : buttonVector)
	{
		b->draw(app);
	}
}

void Battle::leftClick(int x, int y)
{
	for (auto b : buttonVector)
	{
		if (b->isClick(x, y))
		{
			b->doWork();
		}
	}
}

void Battle::doubleClick(int x, int y)
{
	;
}

void Battle::rightClick(int x, int y)
{
	;
}
