#pragma once

#include "Utility.h"

#include <vector>
#include <memory>

struct Deck
{
	Deck(std::string& n, int c1, int c2, int c3)
		: card{ c1, c2, c3 }
	{
		std::size_t convertNum = 0;
		name = stringToTCHAR(n, convertNum);
		if (convertNum > 16)
		{
			throw std::exception("DECK NAME CANNOT EXCEED 15 CHARACTERS");
		}
	}

	TCHAR* name;
	int card[3];
};

class User
{
public:
	User(char* = "RESOURCE/userInfo.txt");

	void printInfo(Application&) const;

	void levelUp();
	void gemDelta(int);
	void expUp(int);
	void apDelta(int);
	void apMaxUp();

	std::vector<std::shared_ptr<struct Deck>> deckVector;

private:
	TCHAR* name;
	int
		level,
		gem,
		exp,
		apLeft,
		apMax;
};