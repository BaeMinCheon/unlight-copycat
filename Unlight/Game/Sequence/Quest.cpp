#include <Core/Game.h>
#include <Core/User.h>
#include <Sequence/Quest.h>
#include <Sequence/QuestSub.h>
#include <Utility/BRect.h>
#include <Utility/BCirc.h>
#include <Utility/BQuest.h>
#include <Utility/DOne.h>
#include <Utility/DTwo.h>

Quest::Quest(class Game* _pg) :
	Sequence(_pg),
	mCurDeck(0)
{
	this->create();
}

Quest::~Quest()
{
	this->quit();
}

void Quest::create()
{
	mBVector.push_back(new BCirc(this, 750, 25, 20.0f, "BACK"));
	mBVector.back()->setFunc(0, [this]()
	{
		mGame->setCurSeq("Main");
	});

	mBVector.push_back(new BRect(this, 10, 727, 30, 30, "<"));
	mBVector.back()->setFunc(0, [this]()
	{
		--mCurDeck;
		if (mCurDeck < 0)
		{
			mCurDeck = 2;
		}
	});

	mBVector.push_back(new BRect(this, 70, 727, 30, 30, ">"));
	mBVector.back()->setFunc(0, [this]()
	{
		++mCurDeck;
		if (mCurDeck > 2)
		{
			mCurDeck = 0;
		}
	});

	this->addBQuest(new BQuest(this, "TEST01", 1));
	this->addBQuest(new BQuest(this, "TEST02", 2));
	this->addBQuest(new BQuest(this, "TEST03", 3));
	this->addBQuest(new BQuest(this, "TEST04", 4));
	this->addBQuest(new BQuest(this, "TEST05", 5));
	this->addBQuest(new BQuest(this, "TEST06", 6));
	this->addBQuest(new BQuest(this, "TEST07", 7));
}

void Quest::quit()
{
	for (auto b : mBVector)
	{
		delete b;
	}
	for (auto b : mQVector)
	{
		delete b;
	}
}

void Quest::mouseDown(int _x, int _y)
{
	for (auto b : mBVector)
	{
		b->mouseDown(_x, _y);
	}
	for (auto q : mQVector)
	{
		q->mouseDown(_x, _y);
	}
}

void Quest::mouseMDown(int _x, int _y)
{
	for (auto b : mBVector)
	{
		b->mouseMDown(_x, _y);
	}
	for (auto q : mQVector)
	{
		q->mouseMDown(_x, _y);
	}
}

void Quest::mouseRDown(int _x, int _y)
{
	for (auto b : mBVector)
	{
		b->mouseRDown(_x, _y);
	}
	for (auto q : mQVector)
	{
		q->mouseRDown(_x, _y);
	}
}

void Quest::doubleClick(int _x, int _y)
{
	for (auto b : mBVector)
	{
		b->doubleClick(_x, _y);
	}
	for (auto q : mQVector)
	{
		q->doubleClick(_x, _y);
	}
}

void Quest::paint(class Application& _ap)
{
	{
		_ap.wout << setpos(100, 15) << TEXT("Quest Sequence");
		_ap.setBrush(gray);
		_ap.rectangle(500, 50, 300, 300);
		_ap.rectangle(0, 525, 800, 200);
		_ap.setBrush(white);
		_ap.rectangle(25, 535, 350, 180);
	}
	{
		auto deck = mGame->getUser()->getDecks()[mCurDeck];
		_ap.wout << setpos(52, 735) << mCurDeck + 1;
		_ap.wout << setpos(120, 735) << deck.mName;
		for (int i = 0; i < 3; ++i)
		{
			if (deck.mCard[i] == 0)
			{
				_ap.rectangle(40 + 110 * i, 550, 100, 150);
			}
			else
			{
				_ap.drawBitmap(mGame->getBMPVec()[deck.mCard[i]], 40 + 110 * i, 550, 200, 300, 0.5);
			}
		}
	}
	{
		for (auto b : mBVector)
		{
			b->paint(_ap);
		}
		for (auto q : mQVector)
		{
			q->paint(_ap);
		}
	}
	{
		mGame->getUser()->paint(_ap);
	}
}

void Quest::timer()
{
	for (auto b : mBVector)
	{
		b->timer();
	}
	for (auto q : mQVector)
	{
		q->timer();
	}

	mGame->getUser()->timer();
}

void Quest::addBQuest(class BQuest* _pq)
{
	if (mQVector.size() >= 7)
	{
		delete _pq;
	}
	else
	{
		mQVector.push_back(_pq);
		this->updateQVec();
	}
}

void Quest::updateQVec()
{
	int height = 60;
	for (auto q : mQVector)
	{
		q->setPos(510, height);
		height += 40;
	}
}

void Quest::eraseBQuest(class BQuest* _pq)
{
	auto iter = std::find(mQVector.begin(), mQVector.end(), _pq);
	if (iter == mQVector.end())
	{
		;
	}
	else
	{
		mQVector.erase(iter);
	}
	this->updateQVec();
}