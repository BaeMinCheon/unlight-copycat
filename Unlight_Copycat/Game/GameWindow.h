#pragma once

#include "Sequence.h"

#include <vector>
#include <memory>

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
};