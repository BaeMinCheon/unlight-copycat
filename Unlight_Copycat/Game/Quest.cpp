#include "Quest.h"
#include "GameWindow.h"

#include <fstream>

int Quest::deckIndex;

// ==============================================================================

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
			Map::mapVector.push_back(std::make_shared<Map>(n, c, l, bArr));
			if (Map::mapVector.size() == 6)
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
		GameWindow::currentSequence = "Main";
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
		Map::mapInProcess = true;
		Map::menuOut();
		Map::menuVector[2]->moveTo(10, 170);
		Map::position = 0;

		GameWindow::player.apDelta(-Map::mapVector[Map::mapListIndex]->getCost());
	}));
	Map::menuVector.push_back(std::make_shared<RectButton>(-800, 0, 70, 50,
		(TCHAR*)TEXT("DELETE"), white, []()
	{
		Map::mapVector[Map::mapListIndex] = nullptr;
		for (unsigned i = Map::mapListIndex; i < Map::mapVector.size() - 1; ++i)
		{
			Map::mapVector[i] = Map::mapVector[i + 1];
			Map::mapVector[i]->list.upList();
		}
		Map::mapVector.pop_back();

		Map::mapListIndex = -1;
		Map::menuOut();
	}));
	Map::menuVector.push_back(std::make_shared<RectButton>(-800, 0, 70, 50,
		(TCHAR*)TEXT("GIVEUP"), white, []()
	{
		Map::mapInProcess = false;
		Map::menuVector[2]->moveTo(-800, 0);
		Map::menuVector[1]->doWork();
		Map::position = -1;
	}));

	Map::mapListIndex = -1;
	Map::mapInProcess = false;
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
	for (auto m : Map::mapVector)
	{
		m->listDraw(app);
	}
	if (Map::mapListIndex != -1)
	{
		Map::mapVector[Map::mapListIndex]->infoDraw(app);
	}
}

void Quest::leftClick(int x, int y)
{
	if (!Map::mapInProcess)
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
			if (Map::mapListIndex != -1)
			{
				for (auto b : Map::mapVector[Map::mapListIndex]->blockVector)
				{
					b->blockOut();
				}
			}
			Map::menuOut();
			Map::mapListIndex = -1;
		}
		for (unsigned i = 0; i < Map::mapVector.size(); ++i)
		{
			if (Map::mapVector[i]->listClick(x, y))
			{
				for (auto b : Map::mapVector[i]->blockVector)
				{
					b->blockIn();
				}
				Map::menuIn();
				if (Map::mapListIndex == -1)
				{
					Map::mapListIndex = i;
				}
				break;
			}
		}
	}
	else
	{
		if (Map::position < Map::mapVector[Map::mapListIndex]->getLength())
		{
			auto& nextBlock = Map::mapVector[Map::mapListIndex]->blockVector[Map::position + 1];
			if (nextBlock->isClick(x, y))
			{
				nextBlock->doWork();
				++Map::position;
				if (Map::position == Map::mapVector[Map::mapListIndex]->getLength())
				{
					Map::menuVector[2]->moveTo(-800, 0);
					Map::clear.moveTo(305, 300);
				}
			}
		}
		if (Map::position == Map::mapVector[Map::mapListIndex]->getLength())
		{
			Map::menuVector[2]->moveTo(-800, 0);
			Map::clear.moveTo(305, 300);

			if (Map::clear.isClick(x, y))
			{
				Map::mapInProcess = false;
				Map::menuVector[2]->doWork();
				Map::clear.moveTo(-800, 0);
			}
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