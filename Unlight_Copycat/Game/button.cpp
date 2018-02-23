#include "button.h"

void Button::setWork(std::function<void()> f)
{
	work = f;
}

void Button::doWork()
{
	work();
}

void Button::setColor(Color c)
{
	color = c;
}

void Button::setName(TCHAR* n)
{
	if (name != nullptr)
	{
		delete[] name;
	}
	name = new TCHAR[_tcslen(n) + 1];
	lstrcpy(name, n);
}

void Button::init()
{
	work = []() {};
	color = white;
	name = new TCHAR[3];
	lstrcpy(name, TEXT(""));
}

// ===============================================================

RectButton::RectButton(int lx, int ly, int wid, int hei)
	: leftX(lx), leftY(ly), width(wid), height(hei)
{
	init();
}

RectButton::RectButton(int lx, int ly, int wid, int hei, TCHAR* n, Color c, std::function<void()> f)
	: leftX(lx), leftY(ly), width(wid), height(hei)
{
	setName(n);
	color = c;
	work = f;
}

bool RectButton::isClick(int x, int y)
{
	if ((x > leftX) && (y > leftY)
		&& (x < leftX + width) && (y < leftY + height))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void RectButton::draw(Application& app)
{
	app.setBrush(color);
	app.rectangle(leftX, leftY, width, height);
	app.setBrush(gray);

	app.wout << setpos(leftX + width / 2 - app.textWidth(name) / 2,
		leftY + height / 2 - app.textHeight() / 2) << name;
}

// ===============================================================

CircButton::CircButton(int cx, int cy, int ra)
	: centerX(cx), centerY(cy), radius(ra)
{
	init();
}

CircButton::CircButton(int cx, int cy, int ra, TCHAR* n, Color c, std::function<void()> f)
	: centerX(cx), centerY(cy), radius(ra)
{
	setName(n);
	color = c;
	work = f;
}

bool CircButton::isClick(int x, int y)
{
	int distance = static_cast<int>(sqrt(pow(centerX - x, 2) + pow(centerY - y, 2)));
	if (distance < radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CircButton::draw(Application& app)
{
	app.setBrush(color);
	app.circle(centerX, centerY, radius);
	app.setBrush(gray);

	app.wout << setpos(centerX - app.textWidth(name) / 2,
		centerY - app.textHeight() / 2) << name;
}