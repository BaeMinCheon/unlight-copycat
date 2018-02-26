#pragma once

#include "Sequence.h"

class MapList : public RectButton
{
public:
	MapList(std::string&, int, int, int*);
	~MapList();

	virtual void draw(Application&);

	int getIndex() const;
	TCHAR* getName() const;
	void decreaseIndex();

private:
	int
		cost,
		length,
		index;
	int* blockArray;
};

class Quest : public Sequence
{
public:
	Quest(char* = "RESOURCE/mapList.txt");

	void init() override;
	void draw(Application&) override;

	void leftClick(int, int) override;
	void doubleClick(int, int) override;
	void rightClick(int, int) override;

	static int deckIndex;
	static std::vector<std::shared_ptr<MapList>> mapVector;
	static int mapListIndex;
};