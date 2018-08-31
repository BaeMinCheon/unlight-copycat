#pragma once

#include <Utility/Button.h>

class BRect : public Button
{
public:
	BRect(class Sequence* _ps, int _x, int _y, int _w, int _h,
		std::string _t);
	~BRect();

	void create() override;
	void quit() override;

	bool isInside(int _x, int _y) override;
	void mouseDown(int _x, int _y) override;
	void mouseMDown(int _x, int _y) override;
	void mouseRDown(int _x, int _y) override;
	void doubleClick(int _x, int _y) override;

	void paint(class Application& _ap) override;
	void timer() override;

private:
	int mWidth;
	int mHeight;
};