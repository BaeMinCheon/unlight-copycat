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

// ===============================================================

int Quest::deckIndex;

Quest::Quest()
{
	init();
}

void Quest::init()
{
	buttonVector.push_back(std::make_shared<RectButton>(730, 10, 60, 30,
		(TCHAR*)TEXT("BACK"), white, []()
	{
		--GameWindow::sequenceIndex;
	}));
	buttonVector.push_back(std::make_shared<RectButton>(10, 727, 30, 30,
		(TCHAR*)TEXT("<"), white, []()
	{
		--Quest::deckIndex;
		if (Quest::deckIndex < 0)
		{
			Quest::deckIndex = 2;
		}
	}));
	buttonVector.push_back(std::make_shared<RectButton>(70, 727, 30, 30,
		(TCHAR*)TEXT(">"), white, []()
	{
		++Quest::deckIndex;
		if (Quest::deckIndex > 2)
		{
			Quest::deckIndex = 0;
		}
	}));
}

void Quest::draw(Application& app)
{
	app.wout << setpos(100, 15) << TEXT("Quest Sequence");

	app.setBrush(gray);
	app.rectangle(500, 50, 300, 300);
	app.rectangle(0, 525, 800, 200);
//	app.rectangle(0, 760, 800, 40);
	app.setBrush(white);
	app.rectangle(25, 535, 350, 180);

	for (auto b : buttonVector)
	{
		b->draw(app);
	}

	GameWindow::player.printInfo(app);

	app.wout << setpos(52, 735) << deckIndex + 1;
//	GameWindow::player.deckVector;
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

// ===============================================================