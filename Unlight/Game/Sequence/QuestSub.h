#pragma once

#include <vector>

#include <Sequence/Sequence.h>

class QuestSub : public Sequence
{
public:
	QuestSub(class Game* _pg, class BQuest* _pq, std::string _n);
	~QuestSub();

	void create() override;
	void quit() override;

	void mouseDown(int _x, int _y) override;
	void mouseMDown(int _x, int _y) override;
	void mouseRDown(int _x, int _y) override;
	void doubleClick(int _x, int _y) override;

	void paint(class Application& _ap) override;
	void timer() override;

private:
	class BQuest* mBQuest;
	TCHAR* mName;
	std::size_t mNameSize;
	std::vector<class Button*> mBVector;
	bool mIsDead;
};