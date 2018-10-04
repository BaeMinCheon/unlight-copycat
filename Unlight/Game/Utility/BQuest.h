#pragma once

#include <Utility/Button.h>

class BQuest : public Button
{
public:
	BQuest(class Quest* _pq, std::string _n, int _c);
	~BQuest();

	void create() override;
	void quit() override;

	bool isInside(int _x, int _y) override;
	void mouseDown(int _x, int _y) override;
	void mouseMDown(int _x, int _y) override;
	void mouseRDown(int _x, int _y) override;
	void doubleClick(int _x, int _y) override;

	void paint(class Application& _ap) override;
	void timer() override;

	class Quest* getQuest();

private:
	class Quest* mQuest;
	std::string mName;
	int mCost;
	
	static int mWidth;
	static int mHeight;
};