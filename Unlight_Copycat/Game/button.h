#pragma once

#include "pclaf.h"

#include <functional>
#include <string>

class Button
{
public:
	Button(int, int);

	virtual bool isClick(int, int) = 0;
	virtual void draw(Application&) = 0;

	virtual void setWork(std::function<void()>);
	virtual void doWork();
	virtual void setColor(Color);
	virtual void setName(TCHAR*);
	virtual void init();
	
	virtual void moveTo(int, int);

protected:
	std::function<void()> work;
	Color color;
	TCHAR* name = nullptr;
	int
		X,
		Y;
};

class RectButton : public Button
{
public:
	RectButton(int, int, int, int);
	RectButton(int, int, int, int, TCHAR*, Color = white, std::function<void()> = []() {});

	virtual bool isClick(int, int) override;
	virtual void draw(Application&) override;
	
protected:
	int 
		width,
		height;
};

class CircButton : public Button
{
public:
	CircButton(int, int, int);
	CircButton(int, int, int, TCHAR*, Color = white, std::function<void()> = []() {});

	virtual bool isClick(int, int) override;
	virtual void draw(Application&) override;

private:
	int	radius;
};

class OKBox : public RectButton
{
public:
	OKBox(int, int, int, int, TCHAR*, Color = white, std::function<void()> = []() {});

	virtual bool isClick(int, int) override;
	virtual void draw(Application&) override;

	virtual void moveTo(int, int) override;

private:
	RectButton ok;
};
