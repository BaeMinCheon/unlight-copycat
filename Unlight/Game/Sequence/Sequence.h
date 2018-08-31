#pragma once

class Sequence
{
public:
	Sequence(class Game* _pg):
		mGame(_pg)
	{
		;
	}
	~Sequence() = default;
	
	virtual void create() = 0;
	virtual void quit() = 0;

	virtual void mouseDown(int _x, int _y) = 0;
	virtual void mouseMDown(int _x, int _y) = 0;
	virtual void mouseRDown(int _x, int _y) = 0;
	virtual void doubleClick(int _x, int _y) = 0;

	virtual void paint(class Application&) = 0;
	virtual void timer() = 0;

	class Game* getGame() { return mGame; }

protected:
	class Game* mGame;
};