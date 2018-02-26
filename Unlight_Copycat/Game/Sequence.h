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