#include "GameWindow.h"

std::vector<std::shared_ptr<Sequence>> GameWindow::sequenceVector;
int GameWindow::sequenceIndex;

GameWindow::GameWindow(TCHAR* title, int wid, int hei, int x, int y)
	: Application(title, wid, hei, x, y)
{
	init();
}

void GameWindow::init()
{
	sequenceVector.push_back(std::make_shared<Main>());
	sequenceVector.push_back(std::make_shared<Quest>());
	sequenceVector.push_back(std::make_shared<Battle>());
	sequenceIndex = 0;
}

void GameWindow::paint()
{
	sequenceVector[sequenceIndex]->draw(*this);
}

void GameWindow::mouseDown(int x, int y)
{
	sequenceVector[sequenceIndex]->leftClick(x, y);

	clearAndUpdate();
}

void GameWindow::doubleClick(int x, int y)
{
	sequenceVector[sequenceIndex]->doubleClick(x, y);

	clearAndUpdate();
}

void GameWindow::mouseRDown(int x, int y)
{
	sequenceVector[sequenceIndex]->rightClick(x, y);

	clearAndUpdate();
}

// ===============================================================

int mainLAF()
{
	GameWindow app(TEXT("Unlight Copycat"), 900, 900, 100, 100);
	app.run();

	return 0;
}