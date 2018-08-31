#include <Core/Game.h>
#include <Sequence/Sequence.h>
#include <Utility/DTwo.h>
#include <Utility/BRect.h>

DTwo::DTwo(class Sequence* _ps, std::string _t):
	Dialog(_ps, _t)
{
	this->create();
}

DTwo::~DTwo()
{
	this->quit();
}

void DTwo::create()
{
	int x = static_cast<int>(mSeq->getGame()->width() / 2 - 150);
	int y = static_cast<int>(mSeq->getGame()->height() / 2);
	int w = 100;
	int h = 50;
	mBOne = new BRect(mSeq, x, y, w, h, "NO");
	mBOne->setFunc(0, [this]()
	{
		mIsDead = true;
	});
	x = static_cast<int>(mSeq->getGame()->width() / 2 + 50);
	y = static_cast<int>(mSeq->getGame()->height() / 2);
	w = 100;
	h = 50;
	mBTwo = new BRect(mSeq, x, y, w, h, "YES");
	mBTwo->setFunc(0, [this]()
	{
		mIsDead = true;

		mFunc();
	});
}

void DTwo::quit()
{
	delete mBOne;
	delete mBTwo;
}

void DTwo::mouseDown(int _x, int _y)
{
	mBOne->mouseDown(_x, _y);
	mBTwo->mouseDown(_x, _y);
}

void DTwo::paint(class Application& _ap)
{
	POINT center = {};
	center.x = static_cast<int>(mPos.first + mWidth / 2 - _ap.textWidth(mText) / 2);
	center.y = static_cast<int>(mPos.second + mHeight / 4 - _ap.textHeight());

	_ap.rectangle(mPos.first, mPos.second, mWidth, mHeight);
	if (mText)
	{
		_ap.wout << setpos(center.x, center.y) << mText;
	}

	mBOne->paint(_ap);
	mBTwo->paint(_ap);
}

void DTwo::timer()
{
	mBOne->timer();
	mBTwo->timer();

	if (mIsDead)
	{
		mSeq->getGame()->setDlg(nullptr);
	}
}