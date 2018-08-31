#pragma once

#include <unordered_map>
#include <string>

#include <Core/pclaf.h>

class Game : public Application
{
public:
	Game(TCHAR* _t, int, int, int, int);
	~Game() = default;

	void create() override;
	void quit() override;
	
	void mouseDown(int _x, int _y) override;
	void mouseMDown(int _x, int _y) override;
	void mouseRDown(int _x, int _y) override;
	void doubleClick(int _x, int _y) override;
	
	void paint() override;
	void timer() override;

	std::unordered_map<std::string, class Sequence*>&	getSeqMap();
	void												setSeqMap(std::string _k, class Sequence* _v);

	std::string&										getCurSeq();
	void												setCurSeq(std::string _k);

	class Dialog*										getDlg();
	void												setDlg(class Dialog* _pd);

	class User*											getUser();
	void												setUser(class User* _pu);

	std::vector<Bitmap>&								getBMPVec();
	void												setBMPvec(int _i, Bitmap& _b);

private:
	std::unordered_map<std::string, class Sequence*> mSeqMap;
	std::string mCurSeq;
	class Dialog* mDlg;
	class User* mUser;
	std::vector<Bitmap> mBMPVec;
};