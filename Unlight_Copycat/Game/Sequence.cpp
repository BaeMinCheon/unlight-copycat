#include "GameWindow.h"

#include <fstream>

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

int MapList::counter;

MapList::MapList(std::string& n, int c, int l, int* p)
	: RectButton(510, 60 + 40 * counter, 280, 30), cost(c), length(l)
{
	std::size_t convertNum = 0;
	name = stringToTCHAR(n, convertNum);
	if (convertNum > 16)
	{
		throw std::exception("MAP NAME CANNOT EXCEED 15 CHARACTERS");
	}

	blockArray = p;

	++counter;
}

MapList::~MapList()
{
	delete[] blockArray;
}

void MapList::draw(Application& app)
{
	app.setBrush(color);
	app.rectangle(leftX, leftY, width, height);
	app.setBrush(gray);

	app.wout << setpos(leftX + 8, leftY + 8) << TEXT("AP");
	app.wout << setpos(leftX + 35, leftY + 8) << cost;
	app.wout << setpos(leftX + width - 10 - app.textWidth(name),
		leftY + height / 2 - app.textHeight() / 2) << name;
}

int Quest::deckIndex;
std::vector<std::shared_ptr<MapList>> Quest::mapVector;

Quest::Quest(char* filename)
{
	std::ifstream mapIn(filename);
	if (mapIn.is_open() == false)
	{
		throw std::exception("MAP LIST CANNOT OPEN");
	}
	std::string buffer;
	while (mapIn >> buffer)
	{
		static std::string n;
		static int
			c,
			l;
		static int* bArr = nullptr;

		if (buffer == "name")
		{
			mapIn >> n;
		}
		else if (buffer == "cost")
		{
			mapIn >> c;
		}
		else if (buffer == "length")
		{
			mapIn >> l;
			bArr = new int[l * 4];
		}
		else if (buffer == "start")
		{
			for (int i = 0; i < l * 4; ++i)
			{
				mapIn >> bArr[i];
			}
		}
		else if (buffer=="end")
		{
			mapVector.push_back(std::make_shared<MapList>(n, c, l, bArr));
		}
	}
	mapIn.close();

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

	auto& currentDeck = GameWindow::player.deckVector[deckIndex];
	app.wout << setpos(52, 735) << deckIndex + 1;
	app.wout << setpos(120, 735) << currentDeck->name;
	for (int i = 0; i < 3; ++i)
	{
		if (currentDeck->card[i] < 0)
		{
			app.rectangle(40 + 110 * i, 550, 100, 150);
		}
		else
		{
			app.drawBitmap(GameWindow::bitmapVector[currentDeck->card[i]], 40 + 110 * i, 550, 200, 300, 0.5);
		}
	}

	for (auto l : mapVector)
	{
		l->draw(app);
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