#pragma once

#include <Utility/Dialog.h>

class DTwo : public Dialog
{
public:
	DTwo(class Sequence* _ps, std::string _t);
	~DTwo();

	void create() override;
	void quit() override;

	void mouseDown(int _x, int _y) override;
	
	void paint(class Application& _ap) override;
	void timer() override;

private:
	class BRect* mBOne;
	class BRect* mBTwo;
};