#pragma once

#include "Sequence.h"
#include "Map.h"

class Quest : public Sequence
{
public:
	Quest(char* = "RESOURCE/mapList.txt");

	void init() override;
	void draw(Application&) override;

	void leftClick(int, int) override;
	void doubleClick(int, int) override;
	void rightClick(int, int) override;

	static int deckIndex;
};