#pragma once

#include "Sequence.h"

class Main : public Sequence
{
public:
	Main();

	void init() override;
	void draw(Application&) override;

	void leftClick(int, int) override;
	void doubleClick(int, int) override;
	void rightClick(int, int) override;
};