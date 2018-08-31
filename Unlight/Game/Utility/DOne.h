#pragma once

#include <Utility/Dialog.h>

class DOne : public Dialog
{
public:
	DOne(class Sequence* _ps, std::string _t);
	~DOne();

	void create() override;
	void quit() override;

	void mouseDown(int _x, int _y) override;

	void paint(class Application& _ap) override;
	void timer() override;

private:
	class BRect* mBOne;
};