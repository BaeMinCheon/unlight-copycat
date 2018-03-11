#pragma once

#include "Sequence.h"
#include "Main.h"
#include "Quest.h"
#include "Battle.h"

#include <map>

const static int NUMBER_OF_BITMAP = 10001;

class GameWindow : public Application
{
public:
	GameWindow(TCHAR*, int, int, int, int);

	void init();
	void paint() override;

	void mouseDown(int, int) override;
	void doubleClick(int, int) override;
	void mouseRDown(int, int) override;

	static std::map<std::string, std::shared_ptr<Sequence>> sequenceMap;
	static std::string currentSequence;
	static User player;
	static std::vector<Bitmap> bitmapVector;
	static std::map<int, TCHAR*> itemNameMap;
};