#include "Main.h"
#include "GameWindow.h"

Main::Main()
{
	init();
}

void Main::init()
{
	buttonVector.push_back(std::make_shared<CircButton>(490, 300, 75,
		(TCHAR*)TEXT("Quest"), white, []()
	{
		++GameWindow::sequenceIndex;
	}));
	buttonVector.push_back(std::make_shared<CircButton>(100, 650, 50,
		(TCHAR*)TEXT("Quit"), white, []()
	{
		DestroyWindow(GetActiveWindow());
	}));
}

void Main::draw(Application& app)
{
	app.wout << setpos(100, 15) << TEXT("Main Sequence");

	app.setBrush(gray);
	app.rectangle(0, 40, 800, 150);
	//	app.rectangle(0, 760, 800, 40);
	app.circle(290, 300, 75);
	//	app.circle(490, 300, 75);
	app.circle(390, 450, 75);
	app.setBrush(white);

	for (auto b : buttonVector)
	{
		b->draw(app);
	}

	GameWindow::player.printInfo(app);
}

void Main::leftClick(int x, int y)
{
	for (auto b : buttonVector)
	{
		if (b->isClick(x, y))
		{
			b->doWork();
		}
	}
}

void Main::doubleClick(int x, int y)
{
	;
}

void Main::rightClick(int x, int y)
{
	;
}