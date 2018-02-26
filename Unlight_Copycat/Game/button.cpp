#include "button.h"

Button::Button(int x, int y)
	: X(x), Y(y)
{
	;
}

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

void Button::moveTo(int x, int y)
{
	X = x;
	Y = y;
}

// ===============================================================

RectButton::RectButton(int lx, int ly, int wid, int hei)
	: Button(lx, ly), width(wid), height(hei)
{
	init();
}

RectButton::RectButton(int lx, int ly, int wid, int hei, TCHAR* n, Color c, std::function<void()> f)
	: Button(lx, ly), width(wid), height(hei)
{
	setName(n);
	color = c;
	work = f;
}

bool RectButton::isClick(int x, int y)
{
	if ((x > X) && (y > Y)
		&& (x < X + width) && (y < Y + height))
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
	app.rectangle(X, Y, width, height);
	app.setBrush(gray);

	app.wout << setpos(X + width / 2 - app.textWidth(name) / 2,
		Y + height / 2 - app.textHeight() / 2) << name;
}

// ===============================================================

CircButton::CircButton(int cx, int cy, int ra)
	: Button(cx, cy), radius(ra)
{
	init();
}

CircButton::CircButton(int cx, int cy, int ra, TCHAR* n, Color c, std::function<void()> f)
	: Button(cx, cy), radius(ra)
{
	setName(n);
	color = c;
	work = f;
}

bool CircButton::isClick(int x, int y)
{
	int distance = static_cast<int>(sqrt(pow(X - x, 2) + pow(Y - y, 2)));
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
	app.circle(X, Y, radius);
	app.setBrush(gray);

	app.wout << setpos(X - app.textWidth(name) / 2,
		Y - app.textHeight() / 2) << name;
}