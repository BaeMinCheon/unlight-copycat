#include <Core/Game.h>
#include <Sequence/Sequence.h>
#include <Utility/BRect.h>

BRect::BRect(class Sequence* _ps, int _x, int _y, int _w, int _h,
	std::string _t):
	Button(_ps, _x, _y, _t),
	mWidth(_w),
	mHeight(_h)
{
	this->create();
}

BRect::~BRect()
{
	this->quit();
}

void BRect::create()
{
	;
}

void BRect::quit()
{
	;
}

bool BRect::isInside(int _x, int _y)
{
	if ((_x >= mPos.first) && (_x <= (mPos.first + mWidth)) &&
		(_y >= mPos.second) && (_y <= (mPos.second + mHeight)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BRect::mouseDown(int _x, int _y)
{
	if (this->isInside(_x, _y))
	{
		mState = BState::Click;

		mFunc[0]();
	}
	else
	{
		mState = BState::None;
	}
}

void BRect::mouseMDown(int _x, int _y)
{
	if (this->isInside(_x, _y))
	{
		mState = BState::Click;

		mFunc[1]();
	}
	else
	{
		mState = BState::None;
	}
}

void BRect::mouseRDown(int _x, int _y)
{
	if (this->isInside(_x, _y))
	{
		mState = BState::Click;

		mFunc[2]();
	}
	else
	{
		mState = BState::None;
	}
}

void BRect::doubleClick(int _x, int _y)
{
	if (this->isInside(_x, _y))
	{
		mState = BState::Click;

		mFunc[3]();
	}
	else
	{
		mState = BState::None;
	}
}

void BRect::paint(class Application& _ap)
{
	Color color;
	switch (mState)
	{
	case BState::None:
		color = Color::white;
		break;
	case BState::Hover:
		color = Color::gray;
		break;
	case BState::Click:
		color = Color::black;
		mState = BState::Hover;
		break;
	}

	POINT center = {};
	center.x = static_cast<int>(mPos.first + mWidth / 2 - _ap.textWidth(mText) / 2);
	center.y = static_cast<int>(mPos.second + mHeight / 2 - _ap.textHeight() / 2);

	_ap.setBrush(color);
	_ap.rectangle(mPos.first, mPos.second, mWidth, mHeight);
	if (mText)
	{
		_ap.wout << setpos(center.x, center.y) << mText;
	}
	_ap.setBrush(Color::white);
}

void BRect::timer()
{
	POINT cursor = {};
	GetCursorPos(&cursor);
	ScreenToClient(mSeq->getGame()->handle(), &cursor);
	
	if (this->isInside(cursor.x, cursor.y))
	{
		if (mState == BState::Click)
		{
			;
		}
		else
		{
			mState = BState::Hover;
		}
	}
	else
	{
		mState = BState::None;
	}
}