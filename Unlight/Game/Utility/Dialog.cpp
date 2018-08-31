#include <Core/Game.h>
#include <Sequence/Sequence.h>
#include <Utility/Utility.h>
#include <Utility/Dialog.h>

Dialog::Dialog(class Sequence* _ps, std::string _t):
	mSeq(_ps),
	mPos(0, 0),
	mText(nullptr),
	mIsDead(false)
{
	this->setText(_t);
	mFunc = []() {};
}

Dialog::~Dialog()
{
	if (mText)
	{
		delete[] mText;
	}
}

void Dialog::setText(std::string& _t)
{
	if (mText)
	{
		delete[] mText;
	}

	if (_t == "")
	{
		;
	}
	else
	{
		mText = mText = Utility::getTCHAR(_t, &mTextSize);

		mPos.first = static_cast<int>(mSeq->getGame()->width() / 2 - mSeq->getGame()->textWidth(mText) - 100);
		mWidth = 2 * (mSeq->getGame()->textWidth(mText) + 100);
		mPos.second = static_cast<int>(mSeq->getGame()->height()/2 - mSeq->getGame()->textHeight() - 50);
		mHeight = 2 * (mSeq->getGame()->textHeight() + 50);
	}
}

void Dialog::setFunc(std::function<void()> _f)
{
	mFunc = _f;
}