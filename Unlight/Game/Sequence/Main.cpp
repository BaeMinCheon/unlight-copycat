#include <Core/Game.h>
#include <Core/User.h>
#include <Sequence/Main.h>
#include <Utility/BRect.h>
#include <Utility/BCirc.h>
#include <Utility/DOne.h>
#include <Utility/DTwo.h>

Main::Main(class Game* _pg):
	Sequence(_pg)
{
	this->create();
}

Main::~Main()
{
	this->quit();
}

void Main::create()
{
	mBVector.push_back(new BCirc(this, 490, 300, 75.0f, "Quest"));
	mBVector.back()->setFunc(0, [this]()
	{
		mGame->setCurSeq("Quest");
	});

	mBVector.push_back(new BCirc(this, 100, 650, 50.0f, "Quit"));
	mBVector.back()->setFunc(0, [this]()
	{
		mGame->setDlg(new DTwo(this, "WANNA QUIT ?"));
		mGame->getDlg()->setFunc([this]()
		{
			mGame->quit();
		});
	});
}

void Main::quit()
{
	for (auto b : mBVector)
	{
		delete b;
	}
}

void Main::mouseDown(int _x, int _y)
{
	for (auto b : mBVector)
	{
		b->mouseDown(_x, _y);
	}
}

void Main::mouseMDown(int _x, int _y)
{
	for (auto b : mBVector)
	{
		b->mouseMDown(_x, _y);
	}
}

void Main::mouseRDown(int _x, int _y)
{
	for (auto b : mBVector)
	{
		b->mouseRDown(_x, _y);
	}
}

void Main::doubleClick(int _x, int _y)
{
	for (auto b : mBVector)
	{
		b->doubleClick(_x, _y);
	}
}

void Main::paint(class Application& _ap)
{
	{
		_ap.wout << setpos(100, 15) << TEXT("Main Sequence");
		_ap.setBrush(gray);
		_ap.rectangle(0, 40, 800, 150);
		_ap.circle(290, 300, 75);
		_ap.circle(390, 450, 75);
		_ap.setBrush(white);
	}
	{
		for (auto b : mBVector)
		{
			b->paint(_ap);
		}
	}
	{
		mGame->getUser()->paint(_ap);
	}
}

void Main::timer()
{
	for (auto b : mBVector)
	{
		b->timer();
	}

	mGame->getUser()->timer();
}