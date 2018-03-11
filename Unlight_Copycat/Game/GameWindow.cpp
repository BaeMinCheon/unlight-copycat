#include "GameWindow.h"

std::map<std::string, std::shared_ptr<Sequence>> GameWindow::sequenceMap;
std::string GameWindow::currentSequence;
User GameWindow::player;
std::vector<Bitmap> GameWindow::bitmapVector;
std::map<int, TCHAR*> GameWindow::itemNameMap;

GameWindow::GameWindow(TCHAR* title, int wid, int hei, int x, int y)
	: Application(title, wid, hei, x, y)
{
	init();
}

void GameWindow::init()
{
	sequenceMap["Main"] = std::make_shared<Main>();
	sequenceMap["Quest"] = std::make_shared<Quest>();
	sequenceMap["Battle"] = std::make_shared<Battle>();

	currentSequence = "Main";

	for (int i = 0; i < NUMBER_OF_BITMAP; ++i)
	{
		bitmapVector.push_back(loadBitmap(i + 1));
	}

	itemNameMap[10000] = TEXT("GEM");
}

void GameWindow::paint()
{
	sequenceMap[currentSequence]->draw(*this);
}

void GameWindow::mouseDown(int x, int y)
{
	sequenceMap[currentSequence]->leftClick(x, y);

	clearAndUpdate();
}

void GameWindow::doubleClick(int x, int y)
{
	sequenceMap[currentSequence]->doubleClick(x, y);

	clearAndUpdate();
}

void GameWindow::mouseRDown(int x, int y)
{
	sequenceMap[currentSequence]->rightClick(x, y);

	clearAndUpdate();
}

// ===============================================================

int mainLAF()
{
	GameWindow app(TEXT("Unlight Copycat"), 800, 800, 100, 100);
	app.run();

	return 0;
}