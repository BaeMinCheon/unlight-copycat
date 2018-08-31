#include <Utility/Utility.h>
#include <Utility/Button.h>

Button::Button(class Sequence* _ps, int _x, int _y, std::string _t):
	mSeq(_ps),
	mState(BState::None),
	mPos(_x, _y),
	mText(nullptr)
{
	this->setText(_t);
	mFunc[0] = mFunc[1] = mFunc[2] = mFunc[3] = []() {};
}

Button::~Button()
{
	if (mText)
	{
		delete[] mText;
	}
}

void Button::setText(std::string& _t)
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
		mText = Utility::getTCHAR(_t, &mTextSize);
	}
}

void Button::setFunc(int _i, std::function<void()> _f)
{
	if (0 <= _i && _i <= 3)
	{
		mFunc[_i] = _f;
	}
}