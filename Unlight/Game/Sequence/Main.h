#pragma once

#include <vector>

#include <Sequence/Sequence.h>

class Main : public Sequence
{
public:
	Main(class Game* _pg);
	~Main();
	
	void create() override;
	void quit() override;

	void mouseDown(int _x, int _y) override;
	void mouseMDown(int _x, int _y) override;
	void mouseRDown(int _x, int _y) override;
	void doubleClick(int _x, int _y) override;

	void paint(class Application& _ap) override;
	void timer() override;

private:
	std::vector<class Button*> mBVector;
};