#include "Quest.h"
#include "GameWindow.h"

#include <fstream>

std::vector<std::shared_ptr<RectButton>> Map::menuVector;
RectButton Map::back(-800, 0, 400, 460);
int Map::position = -1;
OKBox Map::clear(-800, 0, 190, 100, TEXT("QUEST CLEAR"));

Map::Map(std::string& n, int c, int l, int* b)
	: list(510, 60 + 40 * Quest::mapVector.size(), 280, 30, c),
	cost(c), length(l), block(b)
{
	std::size_t convertNum = 0;
	name = stringToTCHAR(n, convertNum);
	if (convertNum > 16)
	{
		throw std::exception("MAP NAME CANNOT EXCEED 15 CHARACTERS");
	}

	list.setName(name);

	blockVector.push_back(std::make_shared<MapBlock>(290 - 800, 100, 12));
	for (int i = 0; i < length; ++i)
	{
		blockVector.push_back(std::make_shared<MapBlock>(290 - 800, 150 + 55 * i, 20));
	}
}

Map::~Map()
{
	delete block;
}

void Map::listDraw(Application& app)
{
	list.draw(app);
}

bool Map::listClick(int x, int y)
{
	return list.isClick(x, y);
}

void Map::infoDraw(Application& app)
{
	back.draw(app);
	app.rectangle(285, 100, 10, (blockVector.size() - 1) * 50);
	for (auto b : blockVector)
	{
		b->draw(app);
	}
	if (Quest::mapListIndex >= 0)
	{
		app.wout << setpos(110, 60) <<
			Quest::mapVector[Quest::mapListIndex]->getName();
	}
	if (position >= 0)
	{
		app.setBrush(brightRed);
		app.rectangle(285, 85 + position * 55, 10, 20);
		app.setBrush(gray);
	}
	if (position == Quest::mapVector[Quest::mapListIndex]->getLength())
	{
		clear.draw(app);
	}
}

bool Map::infoClick(int x, int y)
{
	return back.isClick(x, y);
}

TCHAR* Map::getName() const
{
	return name;
}

int Map::getLength() const
{
	return length;
}

void Map::menuIn()
{
	menuVector[0]->moveTo(10, 50);
	menuVector[1]->moveTo(10, 110);
}

void Map::menuOut()
{
	menuVector[0]->moveTo(-800, 0);
	menuVector[1]->moveTo(-800, 0);
}

bool Map::menuClick(int x, int y)
{
	for (auto m : menuVector)
	{
		if (m->isClick(x, y))
		{
			return true;
		}
	}
	return false;
}

void Map::menuDraw(Application& app)
{
	for (auto m : menuVector)
	{
		m->draw(app);
	}
}

// ==============================================================================

int Quest::deckIndex;
std::vector<std::shared_ptr<Map>> Quest::mapVector;
int Quest::mapListIndex;
bool Quest::mapInProcess;

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
			if (l > 5)
			{
				throw std::exception("MAP LENGTH CANNOT EXCEED 5 BLOCK");
			}

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
			mapVector.push_back(std::make_shared<Map>(n, c, l, bArr));
			if (mapVector.size() == 4)
			{
				break;
			}
		}
		else
		{
			throw std::exception("ILLEGAL MAP LIST");
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
	
	Map::menuVector.push_back(std::make_shared<RectButton>(-800, 0, 70, 50,
		(TCHAR*)TEXT("START"), white, []()
	{
		mapInProcess = true;
		Map::menuOut();
		Map::menuVector[2]->moveTo(10, 170);
		Map::position = 0;
	}));
	Map::menuVector.push_back(std::make_shared<RectButton>(-800, 0, 70, 50,
		(TCHAR*)TEXT("DELETE"), white, []()
	{
		mapVector[mapListIndex] = nullptr;
		for (unsigned i = mapListIndex; i < mapVector.size() - 1; ++i)
		{
			mapVector[i] = mapVector[i + 1];
			mapVector[i]->list.upList();
		}
		mapVector.pop_back();

		mapListIndex = -1;
		Map::menuOut();
	}));
	Map::menuVector.push_back(std::make_shared<RectButton>(-800, 0, 70, 50,
		(TCHAR*)TEXT("GIVEUP"), white, []()
	{
		mapInProcess = false;\
		Map::menuVector[2]->moveTo(-800, 0);
		Map::menuVector[1]->doWork();
		Map::position = -1;
	}));

	mapListIndex = -1;
	mapInProcess = false;
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

	Map::menuDraw(app);
	for (auto m : mapVector)
	{
		m->listDraw(app);
	}
	if (mapListIndex != -1)
	{
		mapVector[mapListIndex]->infoDraw(app);
	}
}

void Quest::leftClick(int x, int y)
{
	if (!mapInProcess)
	{
		for (auto b : buttonVector)
		{
			if (b->isClick(x, y))
			{
				b->doWork();
				break;
			}
		}

		if (!Map::menuClick(x, y) && !Map::infoClick(x, y))
		{
			if (mapListIndex != -1)
			{
				for (auto b : mapVector[mapListIndex]->blockVector)
				{
					b->blockOut();
				}
			}
			Map::menuOut();
			mapListIndex = -1;
		}
		for (unsigned i = 0; i < mapVector.size(); ++i)
		{
			if (mapVector[i]->listClick(x, y))
			{
				for (auto b : mapVector[i]->blockVector)
				{
					b->blockIn();
				}
				Map::menuIn();
				if (mapListIndex == -1)
				{
					mapListIndex = i;
				}
				break;
			}
		}
	}
	else
	{
		if (Map::position == mapVector[mapListIndex]->getLength())
		{
			Map::menuVector[2]->moveTo(-800, 0);
			Map::clear.moveTo(305, 300);

			if (Map::clear.isClick(x, y))
			{
				mapInProcess = false;
				Map::menuVector[2]->doWork();
				Map::clear.moveTo(-800, 0);
			}
		}
		else if (mapVector[mapListIndex]->blockVector[Map::position + 1]->isClick(x, y))
		{
			++Map::position;
		}
	}
}

void Quest::doubleClick(int x, int y)
{
	for (auto b : Map::menuVector)
	{
		if (b->isClick(x, y))
		{
			b->doWork();
		}
	}
}

void Quest::rightClick(int x, int y)
{
	;
}