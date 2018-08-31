#include <fstream>
#include <exception>
#include <sstream>

#include <Core/User.h>
#include <Utility/Utility.h>

User::User(class Game* _pg, char* _uf, char* _df):
	mGame(_pg),
	mUserFile(_uf),
	mDeckFile(_df),
	mName(nullptr)
{
	for (int i = 0; i < 3; ++i)
	{
		mDecks[i].mName = nullptr;
		mDecks[i].mCard[0] = mDecks[i].mCard[1] = mDecks[i].mCard[2] = 0;
	}

	this->create();
}

User::~User()
{
	this->quit();
}

void User::create()
{
	loadUser();
	loadDeck();
}

void User::quit()
{
	if (mName)
	{
		delete[] mName;
	}
}

void User::paint(class Application& _ap)
{
	_ap.setBrush(gray);
	_ap.rectangle(0, 760, 800, 40);
	_ap.setBrush(white);

	if (mName)
	{
		_ap.rectangle(5, 765, 200, 30);
		_ap.wout << setpos(10, 770) << TEXT("NAME");
		_ap.wout << setpos(195 - _ap.textWidth(mName), 770) << mName;

		_ap.rectangle(210, 765, 150, 30);
		_ap.wout << setpos(215, 770) << TEXT("LEVEL");
		_ap.wout << setpos(320 - (mLevel >= 100) * 20, 770) << mLevel;

		_ap.rectangle(365, 765, 150, 30);
		_ap.wout << setpos(370, 770) << TEXT("GEM");
		_ap.wout << setpos(480 - (mGem >= 100) * 20, 770) << mGem;

		_ap.rectangle(520, 765, 150, 30);
		_ap.wout << setpos(525, 770) << TEXT("EXP");
		_ap.wout << setpos(630 - (mExp >= 100) * 20, 770) << mExp;

		_ap.circle(735, 740, 50);
		_ap.wout << setpos(710 - (mCurAP >= 100) * 10, 730) << mCurAP;
		_ap.wout << setpos(735, 730) << TEXT("/");
		_ap.wout << setpos(745, 730) << mMaxAP;
	}
}

void User::timer()
{
	;
}

TCHAR* User::getName()
{
	return mName;
}

void User::setName(std::string _n)
{
	if (mName)
	{
		delete[] mName;
	}

	if (_n == "")
	{
		;
	}
	else
	{
		const char* s = _n.c_str();
		std::size_t l = _n.size() + 1;

		mName = new TCHAR[l];
		mbstowcs_s(&mNameSize, mName, l, s, l);
	}
}

int User::getLevel()
{
	return mLevel;
}

void User::setLevel(int _l)
{
	mLevel = _l;
}

int User::getGem()
{
	return mGem;
}

void User::setGem(int _g)
{
	mGem = _g;
}

int User::getExp()
{
	return mExp;
}

void User::setExp(int _e)
{
	mExp = _e;
}

int User::getCurAP()
{
	return mCurAP;
}

void User::setCurAP(int _ca)
{
	mCurAP = _ca;
}

int User::getMaxAP()
{
	return mMaxAP;
}

void User::setMaxAP(int _ma)
{
	mMaxAP = _ma;
}

struct DeckInfo* User::getDecks()
{
	return mDecks;
}

void User::setDecks(struct DeckInfo* _pd)
{
	mDecks[0] = _pd[0];
	mDecks[1] = _pd[1];
	mDecks[2] = _pd[2];
}

std::unordered_map<std::string, int> User::gCardMap
{
	{ "none",			0 },
	{ "evarist_n1",		1 },
	{ "evarist_n2",		2 },
	{ "evarist_n3",		3 },
	{ "izac_n1",		11 },
	{ "izac_n2",		12 },
	{ "grunwald_n1",	21 }
};

void User::loadUser()
{
	std::ifstream input(mUserFile);
	if (!input.is_open())
	{
		throw std::exception("USER FILE CANNOT OPEN");
	}

	std::string buffer;
	std::string former;
	std::string later;
	std::stringstream trimmer;
	for(int i = 0; i < 6; ++i)
	{
		std::getline(input, buffer);

		std::size_t index;
		index = buffer.find(":");
		if (index == std::string::npos)
		{
			throw std::exception("USER FILE FORMAT ERROR");
		}

		former = buffer.substr(0, index);
		trimmer << former;
		former.clear();
		trimmer >> former;
		later = buffer.substr(index + 1, buffer.size());
		trimmer << later;
		later.clear();
		trimmer >> later;
		trimmer.clear();

		if (former == "name")
		{
			mName = Utility::getTCHAR(later, &mNameSize);
		}
		else if (former == "level")
		{
			mLevel = std::stoi(later);
		}
		else if (former == "gem")
		{
			mGem = std::stoi(later);
		}
		else if (former == "exp")
		{
			mExp = std::stoi(later);
		}
		else if (former == "cur_ap")
		{
			mCurAP = std::stoi(later);
		}
		else if (former == "max_ap")
		{
			mMaxAP = std::stoi(later);
		}
	}

	input.close();
}

void User::loadDeck()
{
	std::ifstream input(mDeckFile);
	if (!input.is_open())
	{
		throw std::exception("DECK FILE CANNOT OPEN");
	}

	std::string buffer;
	std::string former;
	std::string later;
	std::stringstream trimmer;
	std::size_t index;
	for (int i = 0; i < 3; ++i)
	{
		std::getline(input, buffer);
		index = buffer.find("{");
		if (index == std::string::npos)
		{
			throw std::exception("DECK FILE FORMAT ERROR");
		}

		for (int j = 0; j < 4; ++j)
		{
			std::getline(input, buffer);

			index = buffer.find(":");
			if (index == std::string::npos)
			{
				throw std::exception("DECK FILE FORMAT ERROR");
			}

			former = buffer.substr(0, index);
			trimmer << former;
			former.clear();
			trimmer >> former;
			later = buffer.substr(index + 1, buffer.size());
			trimmer << later;
			later.clear();
			trimmer >> later;
			trimmer.clear();

			if (former == "name")
			{
				mDecks[i].mName = Utility::getTCHAR(later, &mNameSize);
			}
			else if (former == "first")
			{
				mDecks[i].mCard[0] = gCardMap[later];
			}
			else if (former == "second")
			{
				mDecks[i].mCard[1] = gCardMap[later];
			}
			else if (former == "third")
			{
				mDecks[i].mCard[2] = gCardMap[later];
			}
		}

		std::getline(input, buffer);
		index = buffer.find("}");
		if (index == std::string::npos)
		{
			throw std::exception("DECK FILE FORMAT ERROR");
		}
	}

	input.close();
}