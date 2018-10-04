#pragma once

#include <vector>

#include <Sequence/Sequence.h>

class Quest : public Sequence
{
public:
	Quest(class Game* _pg);
	~Quest();

	void create() override;
	void quit() override;

	void mouseDown(int _x, int _y) override;
	void mouseMDown(int _x, int _y) override;
	void mouseRDown(int _x, int _y) override;
	void doubleClick(int _x, int _y) override;

	void paint(class Application& _ap) override;
	void timer() override;

	void addBQuest(class BQuest* _pq);
	void updateQVec();
	void eraseBQuest(class BQuest* _pq);

private:
	std::vector<class Button*> mBVector;
	int mCurDeck;
	std::vector<class BQuest*> mQVector;
	int mCurQuest;
};