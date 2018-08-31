#pragma once

#include <utility>
#include <string>
#include <tchar.h>
#include <functional>

enum BState
{
	None,
	Hover,
	Click
};

class Button
{
public:
	Button(class Sequence* _ps, int _x, int _y, std::string _t);
	virtual ~Button();

	virtual void create() = 0;
	virtual void quit() = 0;

	virtual bool isInside(int _x, int _y) = 0;
	virtual void mouseDown(int _x, int _y) = 0;
	virtual void mouseMDown(int _x, int _y) = 0;
	virtual void mouseRDown(int _x, int _y) = 0;
	virtual void doubleClick(int _x, int _y) = 0;

	virtual void paint(class Application& _ap) = 0;
	virtual void timer() = 0;
	
	virtual void setText(std::string& _t);
	virtual void setFunc(int _i, std::function<void()> _f);

protected:
	class Sequence* mSeq;
	BState mState;
	std::pair<int, int> mPos;
	TCHAR* mText;
	std::size_t mTextSize;
	std::function<void()> mFunc[4];
};