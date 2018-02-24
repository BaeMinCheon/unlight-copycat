#pragma once

#include "pclaf.h"

#include <vector>
#include <memory>
#include <string>

struct Deck
{
	Deck(std::string n, int c1, int c2, int c3)
		: name(n), card01(c1), card02(c2), card03(c3)
	{
		;
	}

	std::string name;
	int
		card01,
		card02,
		card03;
};

class User
{
public:
	User(char* = "RESOURCE/userInfo.txt") throw ( std::exception );

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