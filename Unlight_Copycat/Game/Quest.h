#pragma once

#include "Sequence.h"

class Map
{
	class MapList : public RectButton
	{
	public:
		MapList(int lx, int ly, int wid, int hei, int c)
			: RectButton(lx, ly, wid, hei), cost(c)
		{
			;
		}

		void draw(Application& app) override
		{
			app.setBrush(color);
			app.rectangle(X, Y, width, height);
			app.setBrush(gray);

			app.wout << setpos(X + 8, Y + 8) << TEXT("AP");
			app.wout << setpos(X + 35, Y + 8) << cost;
			app.wout << setpos(X + width - 10 - app.textWidth(name),
				Y + height / 2 - app.textHeight() / 2) << name;
		}
		void upList()
		{
			Y -= 40;
		}

	private:
		int cost;
	};

	class MapBlock : public Button
	{
	public:
		MapBlock(int x, int y, int d, Color c = white, std::function<void()> f = []() {})
			: Button(x, y), distance(d)
		{
			setName(TEXT(""));
			color = c;
			work = f;
		}

		bool isClick(int x, int y)
		{
			int d = static_cast<int>(sqrt(pow(X - x, 2) + pow(Y - y, 2)));
			if (d < distance)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		void draw(Application& app)
		{
			POINT diamond[4] =
			{
				{ X - distance, Y },
				{ X, Y - distance },
				{ X + distance, Y },
				{ X, Y + distance }
			};
			app.setBrush(color);
			app.polygon(diamond, 4);
			app.setBrush(gray);
		}

		void blockIn()
		{
			X += 800;
		}
		void blockOut()
		{
			X -= 800;
		}

	private:
		int distance;
	};

public:
	Map(std::string&, int, int, int*);
	~Map();

	void listDraw(Application& app);
	bool listClick(int, int);
	void blockDraw(Application& app);
	bool blockClick(int, int);

	TCHAR* getName() const;

	MapList list;
	std::vector<std::shared_ptr<MapBlock>> blockVector;

	static void menuIn();
	static void menuOut();
	static bool menuClick(int, int);
	static void menuDraw(Application&);

	static std::vector<std::shared_ptr<RectButton>> menuVector;

private:
	TCHAR* name;
	int
		cost,
		length,
		index;
	int* block;
};

class Quest : public Sequence
{
public:
	Quest(char* = "RESOURCE/mapList.txt");

	void init() override;
	void draw(Application&) override;

	void leftClick(int, int) override;
	void doubleClick(int, int) override;
	void rightClick(int, int) override;

	static int deckIndex;
	static std::vector<std::shared_ptr<Map>> mapVector;
	static int mapListIndex;
	static bool mapInProcess;
};