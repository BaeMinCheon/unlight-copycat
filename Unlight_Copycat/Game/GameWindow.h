#pragma once

#include "Sequence.h"

#include <map>

const static int NUMBER_OF_BITMAP = 1;

class GameWindow : public Application
{
public:
	GameWindow(TCHAR*, int, int, int, int);

	void init();
	void paint() override;

	void mouseDown(int, int) override;
	void doubleClick(int, int) override;
	void mouseRDown(int, int) override;

	static std::vector<std::shared_ptr<Sequence>> sequenceVector;
	static int sequenceIndex;
	static User player;
	static std::vector<Bitmap> bitmapVector;
};