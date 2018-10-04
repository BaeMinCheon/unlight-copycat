#include <Core/Game.h>
#include <Sequence/Quest.h>
#include <Sequence/QuestSub.h>
#include <Utility/Utility.h>
#include <Utility/BRect.h>
#include <Utility/BQuest.h>
#include <Utility/DTwo.h>

QuestSub::QuestSub(class Game* _pg, class BQuest* _pq, std::string _n):
	Sequence(_pg),
	mBQuest(_pq),
	mName(Utility::getTCHAR(_n, &mNameSize)),
	mIsDead(false)
{
	this->create();
}

QuestSub::~QuestSub()
{
	this->quit();
}

void QuestSub::create()
{
	mBVector.push_back(new BRect(this, 10, 50, 70, 50, "START"));
	mBVector.back()->setFunc(0, [this]()
	{
		mGame->setDlg(new DTwo(this, "WANNA START ?"));
		mGame->getDlg()->setFunc([this]()
		{
			mBVector[0]->setPos(-100, 0);
			mBVector[1]->setPos(-100, 0);
			mBVector.push_back(new BRect(this, 10, 50, 70, 50, "GIVE UP"));
			mBVector.back()->setFunc(0, [this]()
			{
				mGame->setDlg(new DTwo(this, "WANNA GIVE UP ?"));
				mGame->getDlg()->setFunc([this]()
				{
					mBQuest->getQuest()->eraseBQuest(mBQuest);
					mGame->setCurSeq("Quest");
					
					mIsDead = true;
				});
			});
		});
	});

	mBVector.push_back(new BRect(this, 10, 110, 70, 50, "DELETE"));
	mBVector.back()->setFunc(0, [this]()
	{
		mGame->setDlg(new DTwo(this, "WANNA DELETE ?"));
		mGame->getDlg()->setFunc([this]()
		{
			mBQuest->getQuest()->eraseBQuest(mBQuest);
			mGame->setCurSeq("Quest");

			mIsDead = true;
		});
	});
}

void QuestSub::quit()
{
	if (mBQuest)
	{
		delete mBQuest;
	}
	for (auto b : mBVector)
	{
		delete b;
	}
}

void QuestSub::mouseDown(int _x, int _y)
{
	for (auto b : mBVector)
	{
		b->mouseDown(_x, _y);
	}
}

void QuestSub::mouseMDown(int _x, int _y)
{
	for (auto b : mBVector)
	{
		b->mouseMDown(_x, _y);
	}
}

void QuestSub::mouseRDown(int _x, int _y)
{
	for (auto b : mBVector)
	{
		b->mouseRDown(_x, _y);
	}
}

void QuestSub::doubleClick(int _x, int _y)
{
	for (auto b : mBVector)
	{
		b->doubleClick(_x, _y);
	}
}

void QuestSub::paint(class Application& _ap)
{
	mBQuest->getQuest()->paint(_ap);

	for (auto b : mBVector)
	{
		b->paint(_ap);
	}
}

void QuestSub::timer()
{
	for (auto b : mBVector)
	{
		b->timer();
	}

	if (mIsDead)
	{
		mGame->setSeqMap("QuestSub", nullptr);
	}
}