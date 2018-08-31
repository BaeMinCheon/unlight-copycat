#include <Core/Game.h>
#include <Core/User.h>
#include <Sequence/Main.h>
#include <Sequence/Quest.h>
#include <Utility/Dialog.h>

Game::Game(TCHAR* _t, int _w, int _h, int _x, int _y):
	Application(_t, _w, _h, _x, _y),
	mDlg(nullptr),
	mUser(nullptr)
{
	this->create();
}

void Game::create()
{
	mUser = new User(this, "Resource/Data/USER.txt", "Resource/Data/DECK.txt");
	for (int i = 0; i < 100; ++i)
	{
		mBMPVec.push_back(loadBitmap(i));
	}

	mSeqMap["Main"] = new Main(this);
	mSeqMap["Quest"] = new Quest(this);
	mCurSeq = "Main";

	this->startTimer(333);
}

void Game::quit()
{
	for (auto seq : mSeqMap)
	{
		delete seq.second;
	}
	if (mDlg)
	{
		delete mDlg;
	}
	if (mUser)
	{
		delete mUser;
	}
	
	this->stopTimer();

	DestroyWindow(this->handle());
}


void Game::mouseDown(int _x, int _y)
{
	if (mDlg)
	{
		mDlg->mouseDown(_x, _y);
	}
	else
	{
		mSeqMap[mCurSeq]->mouseDown(_x, _y);
	}
}

void Game::mouseMDown(int _x, int _y)
{
	if (mDlg)
	{
		mDlg->mouseDown(_x, _y);
	}
	else
	{
		mSeqMap[mCurSeq]->mouseDown(_x, _y);
	}
}

void Game::mouseRDown(int _x, int _y)
{
	if (mDlg)
	{
		mDlg->mouseDown(_x, _y);
	}
	else
	{
		mSeqMap[mCurSeq]->mouseDown(_x, _y);
	}
}

void Game::doubleClick(int _x, int _y)
{
	if (mDlg)
	{
		mDlg->mouseDown(_x, _y);
	}
	else
	{
		mSeqMap[mCurSeq]->mouseDown(_x, _y);
	}
}


void Game::paint()
{
	mSeqMap[mCurSeq]->paint(*this);

	if (mDlg)
	{
		mDlg->paint(*this);
	}
}

void Game::timer()
{
	if (mDlg)
	{
		mDlg->timer();
	}
	else
	{
		mSeqMap[mCurSeq]->timer();
	}

	this->clearAndUpdate();
}

std::unordered_map<std::string, class Sequence*>& Game::getSeqMap()
{
	return mSeqMap;
}

void Game::setSeqMap(std::string _k, class Sequence* _v)
{
	auto iter = mSeqMap.find(_k);
	if (iter == mSeqMap.end())
	{
		;
	}
	else
	{
		delete mSeqMap[_k];
	}

	mSeqMap[_k] = _v;
}

std::string& Game::getCurSeq()
{
	return mCurSeq;
}

void Game::setCurSeq(std::string _k)
{
	mCurSeq = _k;
}

class Dialog* Game::getDlg()
{
	return mDlg;
}

void Game::setDlg(class Dialog* _pd)
{
	if (mDlg)
	{
		delete mDlg;
	}

	mDlg = _pd;
}

class User* Game::getUser()
{
	return mUser;
}

void Game::setUser(class User* _pu)
{
	if (mUser)
	{
		delete mUser;
	}

	mUser = _pu;
}

std::vector<Bitmap>& Game::getBMPVec()
{
	return mBMPVec;
}

void Game::setBMPvec(int _i, Bitmap& _b)
{
	mBMPVec[_i] = _b;
}