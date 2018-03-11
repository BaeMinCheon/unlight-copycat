#pragma once

#include "Button.h"
#include <vector>
#include <memory>

class ItemBox : public RectButton
{
public:
	ItemBox(int, int = 1, Color = white, std::function<void()> f = []() {});

	virtual bool isClick(int, int) override;
	virtual void draw(Application& app) override;

	virtual void moveTo(int, int) override;

private:
	RectButton ok;
	int
		id,
		numberOfItem;
};

class Map
{
private:
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
		MapBlock(int x, int y, int d, std::function<void()> f = []() {})
			: Button(x, y), distance(d)
		{
			setName(TEXT(""));
			color = white;
			work = f;
		}

		bool isClick(int x, int y) override
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
		void draw(Application& app) override
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
			Map::back.moveTo(90, 50);
		}
		void blockOut()
		{
			X -= 800;
			Map::back.moveTo(-800, 0);
		}

	private:
		int distance;
	};

public:
	Map(std::string&, int, int, int*);
	~Map();

	void listDraw(Application& app);
	bool listClick(int, int);
	void infoDraw(Application& app);
	static bool infoClick(int, int);

	TCHAR* getName() const;
	int getLength() const;
	int getCost() const;

	MapList list;
	std::vector<std::shared_ptr<MapBlock>> blockVector;
	static ItemBox test;

	static void menuIn();
	static void menuOut();
	static bool menuClick(int, int);
	static void menuDraw(Application&);

	static std::vector<std::shared_ptr<Map>> mapVector;
	static int mapListIndex;
	static bool mapInProcess;

	static std::vector<std::shared_ptr<RectButton>> menuVector;
	static RectButton back;
	static int position;
	static OKBox clear;

private:
	TCHAR* name;
	int
		cost,
		length,
		index;
	int* block;
};