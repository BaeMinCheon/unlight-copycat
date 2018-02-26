#include "Quest.h"
#include "GameWindow.h"

#include <fstream>

MapList::MapList(std::string& n, int c, int l, int* p)
	: RectButton(510, 60 + 40 * Quest::mapVector.size(), 280, 30),
	cost(c), length(l), index(Quest::mapVector.size())
{
	std::size_t convertNum = 0;
	name = stringToTCHAR(n, convertNum);
	if (convertNum > 16)
	{
		throw std::exception("MAP NAME CANNOT EXCEED 15 CHARACTERS");
	}

	blockArray = p;
}

MapList::~MapList()
{
	delete[] blockArray;
}

void MapList::draw(Application& app)
{
	app.setBrush(color);
	app.rectangle(X, Y, width, height);
	app.setBrush(gray);

	app.wout << setpos(X + 8, Y + 8) << TEXT("AP");
	app.wout << setpos(X + 35, Y + 8) << cost;
	app.wout << setpos(X + width - 10 - app.textWidth(name),
		Y + height / 2 - app.textHeight() / 2) << name;
}

int MapList::getIndex() const
{
	return index;
}

TCHAR* MapList::getName() const
{
	return name;
}

void MapList::decreaseIndex()
{
	index -= 1;
}

int Quest::deckIndex;
std::vector<std::shared_ptr<MapList>> Quest::mapVector;
int Quest::mapListIndex;

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
		else if (buffer == "end")
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
	buttonVector.push_back(std::make_shared<RectButton>(-800, 0, 70, 50,
		(TCHAR*)TEXT("START"), white, []()
	{
		;
	}));
	buttonVector.push_back(std::make_shared<RectButton>(-800, 0, 70, 50,
		(TCHAR*)TEXT("DELETE"), white, []()
	{
		;
	}));
	buttonVector.push_back(std::make_shared<RectButton>(-800, 50, 400, 460,
		(TCHAR*)TEXT(""), white, []()
	{
		;
	}));
	mapListIndex = -1;
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

	if (mapListIndex == -1)
	{
		;
	}
	else
	{
		app.wout << setpos(100, 60) << mapVector[mapListIndex]->getName();
	}
}

void Quest::leftClick(int x, int y)
{
	for (auto b : buttonVector)
	{
		if (b->isClick(x, y))
		{
			b->doWork();
			break;
		}
	}

	if (!buttonVector[3]->isClick(x, y)
		&& !buttonVector[4]->isClick(x, y)
		&& !buttonVector[5]->isClick(x, y))
	{
		for (auto m : mapVector)
		{
			if (m->isClick(x, y))
			{
				buttonVector[3]->moveTo(10, 50);
				buttonVector[4]->moveTo(10, 110);
				buttonVector[5]->moveTo(90, 50);

				mapListIndex = m->getIndex();
				break;
			}
			else
			{
				buttonVector[3]->moveTo(-800, 0);
				buttonVector[4]->moveTo(-800, 0);
				buttonVector[5]->moveTo(-800, 0);

				mapListIndex = -1;
			}
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