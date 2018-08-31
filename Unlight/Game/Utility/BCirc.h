#pragma once

#include <Utility/Button.h>

class BCirc : public Button
{
public:
	BCirc(class Sequence* _ps, int _x, int _y, float _r,
		std::string _t);
	~BCirc();

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
	float mRadius;
};