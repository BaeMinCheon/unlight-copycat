Sequence Summary
================

---

#### GameWindow : public Application

-	member `variable`
	-	`static` sequenceMap
		-	["Main"] = Main
		-	["Quest"] = Quest
		-	["Battle"] = Battle
	-	`static` currentSequence
	-	`static` player
	-	`static` bitmapVector
		-	Bitmap
	-	`static` itemNameMap
-	member `function`
	-	GameWindow(TCHAR*, int, int, int, int)
		-	Application 생성자 호출
		-	init() 호출
	-	void init()
		-	sequenceMap에 시퀀스 추가
		-	currentSequence에 "Main" 대입
		-	bitmapVector에 비트맵 추가
		-	itemNameMap에 아이템 추가
	-	void paint()
		-	sequenceIndex의 시퀀스 출력
	-	void mouseDown(int, int)
		-	sequenceIndex의 시퀀스 좌클릭
	-	doubleClick(int, int)
		-	sequenceIndex의 시퀀스 더블클릭
	-	mouseRDown(int, int)
		-	sequenceIndex의 시퀀스 우클릭

#### Main : public Sequence

-	member `variable`
	-	buttonVector
		-	[0] : Quest로 전환
		-	[1] : Quit
-	member `function`
	-	Main()
		-	init() 호출
	-	void init()
		-	buttonVector에 버튼 추가
	-	void draw(Application&)
		-	배경 출력
		-	buttonVector 모든 원소의 draw() 호출
		-	GameWindow::player.printInfo();
	-	void leftClick(int, int)
		-	buttonVector 모든 원소의 isClick() 호출
			-	해당하는 버튼의 doWork() 호출
	-	void doubleClick(int, int)
	-	void rightClick(int, int)

#### Quest : public Sequence

-	member `variable`

	-	buttonVector
		-	[0] : Main으로 전환
		-	[1] : deckIndex 감소
		-	[2] : deckIndex 증가
		-	[3] : 맵 배경
		-	[4] : 맵 시작
		-	[5] : 맵 삭제
	-	`static` deckIndex

-	member `function`

	-	Quest(char*)
		-	파일을 입력받아 Map 초기화
			-	Map::mapVector에 Map 추가
		-	init() 호출
	-	void init()
		-	buttonVector에 버튼 추가
		-	Map::mapListIndex = -1;
		-	Map::mapInProcess = false;
	-	void draw(Application&)
		-	배경 출력
		-	buttonVector 모든 원소의 draw() 호출
		-	GameWindow::player.printInfo();
		-	GameWindow::player 덱 출력
		-	Map::menuDraw();
		-	Map::mapVector 모든 원소의 listDraw() 호출
		-	선택된 맵의 blockDraw() 호출
	-	void leftClick(int, int)
		-	맵을 진행하지 않고 있다면
			-	buttonVector 모든 원소의 isClick() 호출
				-	해당하는 버튼의 doWork() 호출
			-	맵 메뉴버튼이 클릭되지 않았다면
				-	맵블럭을 화면 밖으로 이동
				-	맵 메뉴버튼을 화면 밖으로 이동
				-	Map::mapListIndex = -1;
			-	Map::mapVector 모든 원소의 listClick() 호출
				-	맵블럭을 화면 안으로 이동
				-	맵 메뉴버튼을 화면 안으로 이동
				-	Map::mapListIndex = i;
		-	맵을 진행하고 있다면
			-	SD캐릭터의 위치가 마지막 맵블럭이라면
				-	포기버튼을 화면 밖으로
				-	클리어버튼을 화면 안으로
				-	클리어버튼의 isClick() 호출
					-	Map::mapInProcess = false;
					-	포기버튼 작동
					-	클리어버튼 화면 밖으로
			-	다음 위치의 맵블럭이 클릭되었다면
				-	++Map::position;
	-	void doubleClick(int, int)
		-	Map::menuVector 모든 원소의 isClick() 호출
			-	해당 버튼의 doWork() 호출
	-	void rightClick(int, int)

#### Battle : public Sequence

-	member `variable`
	-	buttonVector
		-	[0] : Quest로 전환
-	member `function`
	-	Battle()
		-	init() 호출
	-	void init()
		-	buttonVector에 버튼 추가
	-	void draw(Application&)
		-	배경 출력
		-	buttonVector 모든 원소의 draw() 호출
	-	void leftClick(int, int)
		-	buttonVector 모든 원소의 isClick() 호출
			-	해당하는 버튼의 doWork() 호출
	-	void doubleClick(int, int)
	-	void rightClick(int, int)
