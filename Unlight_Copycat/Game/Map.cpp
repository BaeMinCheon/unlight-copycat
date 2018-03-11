#include "Map.h"
#include "GameWindow.h"

ItemBox::ItemBox(int t, int n, Color c, std::function<void()> f)
	: RectButton(305, 225, 190, 250, TEXT(""), c, f),
	ok(X + width / 4, Y + height / 1.2, width / 2, height / 8, TEXT("OK")),
	id(t + 10000), numberOfItem(n)
{
	;
}

bool ItemBox::isClick(int x, int y)
{
	return ok.isClick(x, y);
}

void ItemBox::draw(Application& app)
{
	RectButton::draw(app);
	app.drawBitmap(GameWindow::bitmapVector[id], X + 20, Y + 10, 150, 150);
	app.wout << setpos(X + 30, Y + 175) << GameWindow::itemNameMap[id];
	app.wout << setpos(X + 130, Y + 175) << numberOfItem;
	ok.draw(app);
}

void ItemBox::moveTo(int x, int y)
{
	RectButton::moveTo(x, y);
	ok.moveTo(static_cast<int>(x + width / 4), static_cast<int>(y + height / 1.2));
}

// ==============================================================================

std::vector<std::shared_ptr<Map>> Map::mapVector;
int Map::mapListIndex;
bool Map::mapInProcess;

std::vector<std::shared_ptr<RectButton>> Map::menuVector;
RectButton Map::back(-800, 0, 400, 460);
int Map::position = -1;
OKBox Map::clear(-800, 0, 190, 100, TEXT("QUEST CLEAR"));

ItemBox Map::test(0, 100);

Map::Map(std::string& n, int c, int l, int* b)
	: list(510, 60 + 40 * mapVector.size(), 280, 30, c),
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
	std::function<void()> func = []() {};
	for (int i = 0; i < length; ++i)
	{
		switch (block[4 * i])
		{
		case 0:
			break;
		case 1:
			func = []()
			{
				;
			};
			break;
		case 2:
			func = []()
			{
				GameWindow::currentSequence = "Battle";
			};
			break;
		default:
			throw std::exception("MAPBLOCK TYPE ERROR");
		}
		blockVector.push_back(std::make_shared<MapBlock>(290 - 800, 150 + 55 * i, 20, func));
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
	if (mapListIndex >= 0)
	{
		app.wout << setpos(110, 60) <<
			mapVector[mapListIndex]->getName();
	}
	if (position >= 0)
	{
		app.setBrush(brightRed);
		app.rectangle(285, 85 + position * 55, 10, 20);
		app.setBrush(gray);
	}
	if (position == mapVector[mapListIndex]->getLength())
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

int Map::getCost() const
{
	return cost;
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