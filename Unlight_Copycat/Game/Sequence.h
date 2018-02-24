#pragma once

#include "Button.h"
#include "User.h"

class Sequence
{
public:
	virtual void init() = 0;
	virtual void draw(Application&) = 0;

	virtual void leftClick(int, int) = 0;
	virtual void doubleClick(int, int) = 0;
	virtual void rightClick(int, int) = 0;

protected:
	std::vector<std::shared_ptr<Button>> buttonVector;
};

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

class Quest : public Sequence
{
public:
	Quest();

	void init() override;
	void draw(Application&) override;

	void leftClick(int, int) override;
	void doubleClick(int, int) override;
	void rightClick(int, int) override;

	static int deckIndex;
};

class Battle : public Sequence
{
public:
	Battle();

	void init() override;
	void draw(Application&) override;

	void leftClick(int, int) override;
	void doubleClick(int, int) override;
	void rightClick(int, int) override;
};