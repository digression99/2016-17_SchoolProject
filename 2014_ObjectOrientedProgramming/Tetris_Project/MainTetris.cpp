#include "MainTetris.h"

int main()
{
	int count = 0;
	bool timeCheck1 = false, timeCheck2 = false;
	PlayTetris pt;
	bool escCheck = false;
	//bool isMerged = true;
	clock_t st1, end1;// = clock();
	clock_t st2, end2;
	bool isShiftChecked = false;
	int menuNum = 0;
	bool c = false;

	srand((unsigned)time(NULL));
	setCursorView(0);
	
	while (true)
	{ // menu
		menuNum = menu(pt);
		if (menuNum == -1) 
		{
			break;
		}

		pt.getGameInfo()->defaultSetting(menuNum + 1);
		pt.setMergeMap(menuNum);
		pt.setNextBlock();

		while (true)
		{
			pt.setIsMerged(false);
			pt.setIsFirst(true);
			pt.setKeyFree(false);

			pt.startBlock();

			isShiftChecked = false;
			pt.getGameInfo()->showSetting();


			while (true)
			{
				//pt.printBitMap();
				pt.showMergeMap();

				if (pt.getIsShifted())
				{
					isShiftChecked = true;
					break;
				}
				if (!timeCheck1)
				{
					st1 = clock();
					timeCheck1 = true;
				}
				if (!timeCheck2)
				{
					st2 = clock();
					timeCheck2 = true;
				}
				if (timeCheck1)
				{
					end1 = clock();
				}

				if (timeCheck2)
				{
					end2 = clock();
				}

				if (pt.getIsMerged())
				{
					pt.setNextBlock();
				}

				if (diffclock(st2, end2) > KEY_SPEED)
				{
					pt.setKeyFree(true);
					timeCheck2 = false;
				}

				escCheck = getInput(pt);
				if (escCheck)
				{
					break;
				}

				int dif = diffclock(st1, end1);
				if (diffclock(st1, end1) > pt.getGameInfo()->getSpeed())
				{
					if (!pt.checkBlock())
					{
						pt.downBlock();
					}
					else
					{
						pt.mergeBlock();
						//pt.setIsFirst(false);
						if (!c)//cpt.mergeBlock() == false)
						{
							pt.getGameInfo()->setCombo(1);
						}
					}
					timeCheck1 = false;
					pt.setIsFirst(false);
					//pt.setIsMerged
				}

				if (pt.getIsOver())
				{
					break;
				}
				if (pt.getIsMerged())
				{
 					if (!pt.getIsFirst())
					{
						int y = pt.getMovingBlock()->getAbsp()->getY() + 2 - MAP_TOP;
						if (y == 1)
						{
							pt.setIsOver(true);
						}
					}
					break;
				}
			}
			if (pt.getIsOver())
			{
				break;
			}
			if (pt.getGameInfo()->getLines() <= 0){    //레벨업
				pt.getGameInfo()->setLevel(pt.getGameInfo()->getLevel() + 1);
				pt.getGameInfo()->defaultSetting(pt.getGameInfo()->getLevel());
			}
		}
		if (pt.getIsOver())
		{
			break;
		}
	}
	return 0;
}

int menu(PlayTetris &pt)
{
	int kf;
	char ch;
	char * menuStr[] = {
		"---START---",
		"---EXIT---", };
	char * levelStr[] = {
		"* 난이도 선택 *",
		"||---  1  ---||",
		"||---  2  ---||",
		"||---  3  ---||",
		"||---  4  ---||",
		"||---  5  ---||",
		"||---  6  ---||",
		"||---  7  ---||",
		"||---  8  ---||",
		"||---  9  ---||",
		"||---  10 ---||", };
	bool check = false;
	int basex = 10, basey = 3;
	int length;
	int select = 0;

	while (true)
	{
		length = sizeof(menuStr) / sizeof(*menuStr);
		showMesBox(basex, basey, 10, 3);
		showMenu(basex + 4, 4, menuStr, length);
		ch = inKey(&kf);
		switch (ch)
		{
		case UP_ARROW:
			if (basey > 3) 
			{
				eraseMesBox(basex, basey, 10, 3);
				basey -= 2;
				showMesBox(basex, basey, 10, 3);
				select--;
			}
			break;
		case DOWN_ARROW:
			if (basey < length * 2)
			{
				eraseMesBox(basex, basey, 10, 3);
				basey += 2;
				showMesBox(basex, basey, 10, 3);
				select++;
			}
			break;
		case ENTER:
			check = true;
			break;
		}
		if (check) break;
	}
	if (select == 1) 
	{
		return -1;
	}
	system("cls");
	basex = 10;
	basey = 5;
	select = 1;
	check = false;

	while (true)
	{
		length = sizeof(levelStr) / sizeof(*levelStr);
		showMesBox(basex, basey, 12, 3);
		showMenu(basex + 4, 4, levelStr, length);
		pt.showTetrisMap(select - 1);
		ch = inKey(&kf);
		switch (ch)
		{
		case UP_ARROW:
			if (basey > 4)
			{
				eraseMesBox(basex, basey, 12, 3);
				basey -= 2;
				showMesBox(basex, basey, 12, 3);
				select--;
			}
			break;
		case DOWN_ARROW:
			if (basey < length * 2)
			{
				eraseMesBox(basex, basey, 12, 3);
				basey += 2;
				showMesBox(basex, basey, 12, 3);
				select++;
			}
			break;
		case ENTER:
			check = true;
			break;
		}
		if (check) break;
	}
	system("cls");
	return select - 1;
}

void showMesBox(int x, int y, int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			gotoxy(x + j * 2, y + i);

			if (i == 0 && j == 0)
			{
				cout << D1;
				continue;
			}

			if ((i == 0 && j > 0 && j < w - 1) || (i == h - 1 && j > 0 && j < w - 1))
			{
				cout << D10;
				continue;
			}

			if (i == 0 && j == w - 1)
			{
				cout << D3;
				continue;
			}

			if ((j == 0 || j == w - 1) && (i != 0 && i != h - 1))
			{
				cout << D9;
				continue;
			}

			if (i == h - 1 && j == 0)
			{
				cout << D2;
				continue;
			}

			if (i == h - 1 && j == w - 1)
			{
				cout << D4;
				continue;
			}
			cout << "  ";
		}
	}
}

void eraseMesBox(int x, int y, int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			gotoxy(x + j * 2, y + i);
			cout << "  ";
		}
	}
}

void showMenu(int x, int y, char *str[], int size)
{
	for (int i = 0; i < size; i++)
	{
		gotoxy(x, y + i * 2);
		cout << str[i] << endl;
	}
}

bool getInput(PlayTetris & pt)
{
	bool check = false;
	int key = 0;

	if (GetKeyState(VK_UP) < 0)// & 0x8000 == 1)
	{
		if (pt.getKeyFree())
		{
			if (!pt.rotationCheck())
			{
				pt.rotateBlock();
				//pt.getMovingBlock()->rotate();
			}
		}
	}
	if (GetKeyState(VK_DOWN) < 0)// & 0x8000 == 1)
	{
		if (!pt.checkBlock())
		{
			pt.downBlock();
		}
		else
		{
			pt.setIsMerged(true);
		}
	}
	if (GetKeyState(VK_LEFT) < 0)//& 0x8000 == 1)
	{
		if (pt.getKeyFree())
		{
			if (!pt.checkLeftWall())
			{
				pt.leftBlock();
				//pt.getMovingBlock()->getAbsp()->setX(
				//	pt.getMovingBlock()->getAbsp()->getX() - 2);
			}
		}
	}
	if (GetKeyState(VK_RIGHT) < 0)//& 0x8000 == 1)
	{
		if (pt.getKeyFree())
		{
			if (!pt.checkRightWall())
			{
				pt.rightBlock();
			}
		}
	}
	if (GetKeyState(VK_SPACE) < 0)//& 0x8000 == 1)
	{
		if (pt.getKeyFree())
		{
			if (!pt.getIsMerged())
			{
				while (true)
				{
					if (!pt.checkBlock())
					{
						pt.downBlock();
					}
					else
					{
						pt.mergeBlock();
						pt.setIsMerged(true);
						break;
					}
				}
			}
		}
		//check = true;
		//key = VK_SPACE;               
	}
	if (GetKeyState(VK_ESCAPE) < 0)
	{
		check = true;
		key = VK_ESCAPE;
	}
	if (GetKeyState(VK_SHIFT) < 0)
	{
		if (pt.getIsShifted())
		{
			pt.unShiftBlock();
		}
		else
		{
			pt.shiftBlock();
		}
	}
	//VK_SHIFT

	if (check)
	{
		//dealInput(key, pt);
		if (key == VK_ESCAPE)
		{
			return true;
		}
		return false;
	}
}

void textColor(int foreground, int background)
{
	int 			color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int gotoxy(int x,int y)
{
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
   COORD pos; 
   pos.Y=y;
   pos.X=x;
   SetConsoleCursorPosition(hConsole, pos); 
   return 0;
}

void setCursorView(char visible)
{
   CONSOLE_CURSOR_INFO cursor = {1, visible};
   SetConsoleCursorInfo(GetStdHandle (STD_OUTPUT_HANDLE), &cursor);
}

double diffclock(clock_t clock1,clock_t clock2)
{
    double diffticks=clock1-clock2;
    double diffms=(diffticks)/(CLOCKS_PER_SEC/1000);
    return -diffms;
}


char inKey(int *keyFlag)
{
	char ascii, scan;

	ascii = getch(); // 입력된 문자의 아스키코드를 입력받아옴 
	if (ascii == -32 || ascii == 0){ // 입력된 문자의 아스키코드가 -32이거나 0이면 특수키가 입력된것임 
		scan = getch(); // 특수키가 입력되었을때에는 scan code값을 입력받아옴 
		*keyFlag = SPECIAL_KEY;
		return (scan);
	}
	else { // 일반키가 입력되었으면 
		*keyFlag = COMMON_KEY;
		return (ascii);
	}
}