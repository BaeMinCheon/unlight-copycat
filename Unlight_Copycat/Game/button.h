#pragma once

#include "pclaf.h"

#include <functional>
#include <string>

class Button
{
public:
	virtual bool isClick(int, int) = 0;
	virtual void draw(Application&) = 0;

	virtual void setWork(std::function<void()>);
	virtual void doWork();
	virtual void setColor(Color);
	virtual void setName(TCHAR*);
	virtual void init();

protected:
	std::function<void()> work;
	Color color;
	TCHAR* name = nullptr;
};

class RectButton : public Button
{
public:
	RectButton(int, int, int, int);
	RectButton(int, int, int, int, TCHAR*, Color, std::function<void()>);

	virtual bool isClick(int, int) override;
	virtual void draw(Application&) override;
	
protected:
	int 
		leftX,
		leftY,
		width,
		height;
};

class CircButton : public Button
{
public:
	CircButton(int, int, int);
	CircButton(int, int, int, TCHAR*, Color, std::function<void()>);

	virtual bool isClick(int, int) override;
	virtual void draw(Application&) override;

private:
	int 
		centerX,
		centerY,
		radius;
};