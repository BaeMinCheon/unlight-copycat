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
	buttonVector.push_back(std::make_shared<CircButton>(700, 650, 50,
		(TCHAR*)TEXT("Quit"), white, []()
	{
		DestroyWindow(GetActiveWindow());
	}));
}

void Main::draw(Application& app)
{
	app.wout << setpos(100, 15) << TEXT("Main");
	
	app.setBrush(gray);
	app.rectangle(0, 40, 800, 150);
	app.rectangle(0, 750, 800, 50);
	app.circle(290, 300, 75);
//	app.circle(490, 300, 75);
	app.circle(390, 450, 75);
	app.setBrush(white);

	for (auto b : buttonVector)
	{
		b->draw(app);
	}
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

// ===============================================================

Quest::Quest()
{
	init();
}

void Quest::init()
{
	buttonVector.push_back(std::make_shared<RectButton>(10, 10, 60, 30,
		(TCHAR*)TEXT("Back"), white, []()
	{
		--GameWindow::sequenceIndex;
	}));
	buttonVector.push_back(std::make_shared<RectButton>(730, 10, 60, 30,
		(TCHAR*)TEXT("Battle"), white, []()
	{
		++GameWindow::sequenceIndex;
	}));
}

void Quest::draw(Application& app)
{
	app.wout << setpos(100, 15) << TEXT("Quest");

	for (auto b : buttonVector)
	{
		b->draw(app);
	}
}

void Quest::leftClick(int x, int y)
{
	for (auto b : buttonVector)
	{
		if (b->isClick(x, y))
		{
			b->doWork();
		}
	}
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
	buttonVector.push_back(std::make_shared<RectButton>(10, 10, 60, 30,
		(TCHAR*)TEXT("Back"), white, []()
	{
		--GameWindow::sequenceIndex;
	}));
}

void Battle::draw(Application& app)
{
	app.wout << setpos(100, 15) << TEXT("Battle");

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

// ===============================================================