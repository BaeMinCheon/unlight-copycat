#include <Core/Game.h>
#include <Sequence/Sequence.h>
#include <Utility/DOne.h>
#include <Utility/BRect.h>

DOne::DOne(class Sequence* _ps, std::string _t):
	Dialog(_ps, _t)
{
	this->create();
}

DOne::~DOne()
{
	this->quit();
}

void DOne::create()
{
	int x = static_cast<int>(mSeq->getGame()->width() / 2 - 50);
	int y = static_cast<int>(mSeq->getGame()->height() / 2);
	int w = 100;
	int h = 50;
	mBOne = new BRect(mSeq, x, y, w, h, "OK");
	mBOne->setFunc(0, [this]()
	{
		mIsDead = true;
		
		mFunc();
	});
}

void DOne::quit()
{
	delete mBOne;
}

void DOne::mouseDown(int _x, int _y)
{
	mBOne->mouseDown(_x, _y);
}

void DOne::paint(class Application& _ap)
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
}

void DOne::timer()
{
	mBOne->timer();

	if (mIsDead)
	{
		mSeq->getGame()->setDlg(nullptr);
	}
}