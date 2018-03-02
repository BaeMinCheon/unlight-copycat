#include "User.h"

#include <fstream>

User::User(char* filename)
{
	std::ifstream userIn(filename);
	if (userIn.is_open() == false)
	{
		throw std::exception("USER INFO CANNOT OPEN");
	}
	std::string buffer;
	while (userIn >> buffer)
	{
		if (buffer == "name")
		{
			userIn >> buffer;

			std::size_t convertNum = 0;
			name = stringToTCHAR(buffer, convertNum);
			if (convertNum > 16)
			{
				throw std::exception("USER NAME CANNOT EXCEED 15 CHARACTERS");
			}
		}
		else if (buffer == "level")
		{
			userIn >> level;
		}
		else if (buffer == "gem")
		{
			userIn >> gem;
		}
		else if (buffer == "exp")
		{
			userIn >> exp;
		}
		else if (buffer == "ap")
		{
			userIn >> apLeft;
			userIn >> apMax;
		}
		else if (buffer == "deck")
		{
			std::string n;
			int c1, c2, c3;
			for (int i = 0; i < 3; ++i)
			{
				userIn >> n;
				userIn >> c1;
				userIn >> c2;
				userIn >> c3;

				deckVector.push_back(std::make_shared<struct Deck>(n, c1, c2, c3));
			}
		}
		else
		{
			throw std::exception("ILLEGAL USER INFO");
		}
	}
	userIn.close();
}

void User::printInfo(Application& app) const
{
	app.rectangle(0, 760, 800, 40);

	app.setBrush(white);
	{ // name
		app.rectangle(5, 765, 200, 30);
		app.wout << setpos(10, 770) << TEXT("NAME");
		app.wout << setpos(195 - app.textWidth(name), 770) << name;
	}
	{ // level
		app.rectangle(210, 765, 150, 30);
		app.wout << setpos(215, 770) << TEXT("LEVEL");
		app.wout << setpos(320 - (level >= 100) * 20, 770) << level;
	}
	{ // gem
		app.rectangle(365, 765, 150, 30);
		app.wout << setpos(370, 770) << TEXT("GEM");
		app.wout << setpos(480 - (gem >= 100) * 20, 770) << gem;
	}
	{ // exp
		app.rectangle(520, 765, 150, 30);
		app.wout << setpos(525, 770) << TEXT("EXP");
		app.wout << setpos(630 - (exp >= 100) * 20, 770) << exp;
	}
	{ // ap
		app.circle(735, 740, 50);
		app.wout << setpos(710 - (apLeft >= 100) * 10, 730) << apLeft;
		app.wout << setpos(735, 730) << TEXT("/");
		app.wout << setpos(745, 730) << apMax;
	}
	app.setBrush(gray);
}

void User::levelUp()
{
	++level;
}

void User::gemDelta(int d)
{
	gem += d;
}

void User::expUp(int d)
{
	exp += d;
}

void User::apDelta(int d)
{
	apLeft += d;
	if (apLeft > apMax)
	{
		apLeft = apMax;
	}
}

void User::apMaxUp()
{
	++apMax;
}
