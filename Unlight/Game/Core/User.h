#pragma once

#include <Core/Game.h>

struct DeckInfo
{
	TCHAR* mName;
	int mCard[3];
};

struct QuestInfo
{
	;
};

class User
{
public:
	User(class Game* _pg, char* _uf, char* _df, char* _qf);
	~User();

	void create();
	void quit();

	void paint(class Application& _ap);
	void timer();

	TCHAR*				getName();
	void				setName(std::string _n);

	int					getLevel();
	void				setLevel(int _l);

	int					getGem();
	void				setGem(int _g);

	int					getExp();
	void				setExp(int _e);

	int					getCurAP();
	void				setCurAP(int _ca);

	int					getMaxAP();
	void				setMaxAP(int _ma);

	struct DeckInfo*	getDecks();
	void				setDecks(struct DeckInfo* _pd);

	static std::unordered_map<std::string, int> gCardMap;

private:
	void loadUser();
	void loadDeck();
	void loadQuest();

	class Game* mGame;
	char* mUserFile;
	char* mDeckFile;
	char* mQuestFile;
	TCHAR* mName;
	std::size_t mNameSize;
	int mLevel;
	int mGem;
	int mExp;
	int mCurAP;
	int mMaxAP;
	struct DeckInfo mDecks[3];
};