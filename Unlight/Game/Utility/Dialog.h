#pragma once

#include <utility>
#include <string>
#include <tchar.h>
#include <functional>

class Dialog
{
public:
	Dialog(class Sequence* _ps, std::string _t);
	virtual ~Dialog();

	virtual void create() = 0;
	virtual void quit() = 0;

	virtual void mouseDown(int _x, int _y) = 0;

	virtual void paint(class Application& _ap) = 0;
	virtual void timer() = 0;

	virtual void setText(std::string& _t);
	virtual void setFunc(std::function<void()> _f);

protected:
	class Sequence* mSeq;
	std::pair<int, int> mPos;
	int mWidth;
	int mHeight;
	TCHAR* mText;
	std::size_t mTextSize;
	std::function<void()> mFunc;
	bool mIsDead;
};