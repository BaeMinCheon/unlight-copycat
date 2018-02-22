#pragma once

#include "pclaf.h"

class Sequence
{
public:
	virtual void draw(Application&) = 0;

	virtual void leftClick(int, int);
	virtual void doubleClick(int, int);
	virtual void rightClick(int, int);

private:
	;
};

class Main : public Sequence
{
public:
	Main();

	void init();
	void draw(Application&) override;

	void leftClick(int, int) override;
	void doubleClick(int, int) override;
	void rightClick(int, int) override;
};

class Quest : public Sequence
{
public:
	Quest();

	void init();
	void draw(Application&) override;

	void leftClick(int, int) override;
	void doubleClick(int, int) override;
	void rightClick(int, int) override;
};

class Battle : public Sequence
{
public:
	Battle();

	void init();
	void draw(Application&) override;

	void leftClick(int, int) override;
	void doubleClick(int, int) override;
	void rightClick(int, int) override;
};