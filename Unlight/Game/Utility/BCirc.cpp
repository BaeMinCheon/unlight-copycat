#include <Core/Game.h>
#include <Sequence/Sequence.h>
#include <Utility/BCirc.h>

BCirc::BCirc(class Sequence* _ps, int _x, int _y, float _r,
	std::string _t):
	Button(_ps, _x, _y, _t),
	mRadius(_r)
{
	this->create();
}

BCirc::~BCirc()
{
	this->quit();
}

void BCirc::create()
{
	;
}

void BCirc::quit()
{
	;
}

bool BCirc::isInside(int _x, int _y)
{
	int squareX = static_cast<int>((mPos.first - _x) * (mPos.first - _x));
	int squareY = static_cast<int>((mPos.second - _y) * (mPos.second - _y));
	int squareR = static_cast<int>(mRadius * mRadius);
	
	if ((squareX + squareY) <= squareR)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BCirc::mouseDown(int _x, int _y)
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

void BCirc::mouseMDown(int _x, int _y)
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

void BCirc::mouseRDown(int _x, int _y)
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

void BCirc::doubleClick(int _x, int _y)
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

void BCirc::paint(class Application& _ap)
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
	center.x = static_cast<int>(mPos.first - _ap.textWidth(mText) / 2);
	center.y = static_cast<int>(mPos.second - _ap.textHeight() / 2);

	_ap.setBrush(color);
	_ap.circle(mPos.first, mPos.second, static_cast<int>(mRadius));
	if (mText)
	{
		_ap.wout << setpos(center.x, center.y) << mText;
	}
	_ap.setBrush(Color::white);
}

void BCirc::timer()
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