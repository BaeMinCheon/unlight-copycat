#include <Core/Game.h>
#include <Sequence/Quest.h>
#include <Sequence/QuestSub.h>
#include <Utility/BQuest.h>

BQuest::BQuest(class Quest* _pq, std::string _n, int _c):
	Button(nullptr, 0, 0, _n),
	mName(_n),
	mQuest(_pq),
	mCost(_c)
{
	this->create();
}

BQuest::~BQuest()
{
	this->quit();
}

void BQuest::create()
{
	this->setFunc(0, [this]()
	{
		mQuest->getGame()->setSeqMap("QuestSub", new QuestSub(mQuest->getGame(), this, mName));
		mQuest->getGame()->setCurSeq("QuestSub");
	});
}

void BQuest::quit()
{
	;
}

bool BQuest::isInside(int _x, int _y)
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

void BQuest::mouseDown(int _x, int _y)
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

void BQuest::mouseMDown(int _x, int _y)
{
	;
}

void BQuest::mouseRDown(int _x, int _y)
{
	;
}

void BQuest::doubleClick(int _x, int _y)
{
	;
}

void BQuest::paint(class Application& _ap)
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
	center.x = static_cast<int>(mPos.first + mWidth / 2 - _ap.textWidth(mText) / 2 + 20);
	center.y = static_cast<int>(mPos.second + mHeight / 2 - _ap.textHeight() / 2);

	_ap.setBrush(color);
	_ap.rectangle(mPos.first, mPos.second, mWidth, mHeight);
	if (mText)
	{
		_ap.wout << setpos(center.x, center.y) << mText;
	}
	_ap.wout << setpos(mPos.first + 8, mPos.second + 8) << TEXT("¢½");
	_ap.wout << setpos(mPos.first + 28, mPos.second + 8) << mCost;
	_ap.setBrush(Color::white);
}

void BQuest::timer()
{
	POINT cursor = {};
	GetCursorPos(&cursor);
	ScreenToClient(mQuest->getGame()->handle(), &cursor);

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

class Quest* BQuest::getQuest()
{
	return mQuest;
}

int BQuest::mWidth = 280;
int BQuest::mHeight = 30;