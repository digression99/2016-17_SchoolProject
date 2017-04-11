//
// ����� �α� ����.
//
//
//
#include "Data.h"

int main()
{
	Player player;
	Map arMap[3];
	BOOL key;
	int oldx;
	int oldy;
	int randmini;
	int monster_Frame;
	int monster_FrameF[3]={90,50,5};
	BOOL WinLose;
	char input;
	int level;
	int maptype;
	int level2, level3;
	BOOL ReGame;
	char *str1[] = {
		"������ ������ �ּ���.",
		"(1) ��",
		"(2) ��",
		"(3) ��",
	};
	char *str2[] = {
		"�ٽ� ������ �Ͻðڽ��ϱ�?",
		"��",
		"�ƴϿ�",
	};
	char *str3[] = {
		"���ϴ� �޴��� �����ϼ���.",
		"����ϱ�",
		"�̴ϰ��� ����",
		"���� ����(���� �ٽ� ����)",
		"���� ����",
	};
	char *str4[] = {
		"������ �������� �̴ϰ��ӿ��� �¸��Ͽ��� �Ѵ�.",
		"Ȯ��",
	};
	char *str5[] = {
		"������ �����ڵ��� �ö��� �׿���!",
		"Ȯ��",
	};
	char *str6[] = {
		"������ ã�Ҵ�!",
		"Ȯ��",
	};
	char *str7[] = {
		"������ ���ƴ�. �ٽ� ã�ƾ� �Ѵ�.",
		"Ȯ��",
	};
	char *str8[] = {
		"�̴ϰ����� �����ϼ���.",
		"1. ���������� ����",
		"2. �߱� ����",
	};

	srand((unsigned)time(NULL));

	oldx = INITX;
	oldy = INITY;
	monster_Frame = 0;

	ReGame = FALSE;
	WinLose = FALSE;
	input = 0;
	level = 0;
	maptype = 2;
	level2 = 0;
	level3 = 0;

	removeCursor();
	Init(&player, arMap);
	system("mode con lines=40 cols=100");

	DrawBigBox(strlen(str1[0]), 4);
	level = SelectSquare(str1, sizeof(str1) / sizeof(str1[0]));
	ShowMessage(str1[level]); // �ι�°���� ��ȿ�ϴ�.
	getch();

	while (1)
	{ // ����Ʈ �Լ����� �� �������� �ξ��. �� ����, ����, �÷���, �״��� �÷��̾�.
		if (ReGame)
		{ // ������� ���� ��Ȳ�� �ִ�.
			DrawBigBox(strlen(str2[0]), 3);
			input = SelectSquare(str2, 3); // ����� ���θ� ���´�.
			if (input == 1)
			{
				DrawBigBox(strlen(str1[0]), 4); // ���� �����Ѵ�.
				level = SelectSquare(str1, sizeof(str1) / sizeof(str1[0]));
				ShowMessage(str1[level]); // �ι�°���� ��ȿ�ϴ�.
				getch();

				Init(&player, arMap);
				oldx = INITX;
				oldy = INITY;
				key = FALSE;
				WinLose = FALSE;
				input = 0;
				maptype = 2;
				level2 = 0;
				ReGame = FALSE;
				continue;
			}
			else
			{
				break;
			}
		}

		if (maptype == 1)
		{
			if (GetKeyState(VK_ESCAPE) & 0x8000)
			{
				DrawBigBox(strlen(str3[2]), sizeof(str3) / sizeof(str3[0]));
				level2 = SelectSquare(str3, sizeof(str3) / sizeof(str3[0]));

				switch (level2)
				{
				case 1:
					displayFalse(&player, arMap);
					break;
				case 2:
					DrawBigBox(strlen(str8[0]), sizeof(str8) / sizeof(str8[0]));
					level3 = SelectSquare(str8, sizeof(str8) / sizeof(str8[0]));
					switch (level3)
					{
					case 1:
						Rcp();
						break;
					case 2:
						BallGame();
						break;
					}
					displayFalse(&player, arMap);
					removeCursor();
					break;
				case 3:
					Init(&player, arMap);
					oldx = INITX;
					oldy = INITY;
					monster_Frame = 0;
					removeCursor();
					key = FALSE;
					WinLose = FALSE;
					input = 0;
					level = 1;
					maptype = 2;
					level2 = 0;
					ReGame = TRUE;
					continue;
				case 4:
					return 0;
				}
			}
		}

		if (compare(&player, arMap, &key))
		{
			if (key)
			{
				DrawBigBox(strlen(str4[0]), 2);
				input = SelectSquare(str4, 2);

				randmini = rand() % 2;

				switch (randmini)
				{
				case 0:
					WinLose = BallGame();
					break;
				case 1:
					WinLose = Rcp();
					break;
				}

				if (WinLose)
				{
					DrawBigBox(strlen(str6[0]), 2);
					SelectSquare(str6, 2);
					ReGame = TRUE;
					continue;
				}
				else
				{
					DrawBigBox(strlen(str7[0]), 2);
					SelectSquare(str7, 2);

					Init(&player, arMap);
					oldx = INITX;
					oldy = INITY;
					monster_Frame = 0;
					removeCursor();
					key = FALSE;
					WinLose = FALSE;
					input = 0;
					level = 1;
					maptype = 2;
					level2 = 0;
					ReGame = TRUE;
					continue;
				}
			}
			else
			{
				DrawBigBox(strlen(str5[0]), 2);
				SelectSquare(str5, 2);
				ReGame = TRUE;
				continue;
			}
		}
		Map_Update(&player, arMap);
		Monster_Update(&player, arMap, &monster_Frame, &(monster_FrameF[level - 1]));
		Flag_Update(&player, arMap);
		Player_Update(&player, arMap, &oldx, &oldy);
		maptype = 1;
		Sleep(10);
	}

	return 0;
}

void displayFalse(Player *pp, Map *mp)
{
	int i;
	int j;

	pp->display= FALSE;

	for (i = 0; i < MAP_NUM; i++)
	{
		mp[i].display = FALSE;
		for (j = 0; j < MONSTER_NUM; j++)
		{
			mp[i].arMonster[j].display = FALSE;
			mp[i].arMonster[j].isMoved = TRUE;
		}
		for (j = 0; j < FLAG_NUM; j++)
		{
			mp[i].arFlag[j].display = FALSE;
		}
	}
}

void DeleteMessage(char *str)
{
	int i;
	int j;

	int cent = strlen(str) / 2;

	for (i = 0; i < 6; i++)
	{
		gotoxy(MES_LEFT, MES_UP + i);
		for (j = 0; j < 2 * cent + 2; j++)
		{
			printf("  ");
		}
	}
}

void ShowMessage(char *str)
{
	int i;
	int j;
	int cent = strlen(str) / 2;

	gotoxy(MES_LEFT, MES_UP);
	printf("��");
	for (i = 0; i < 2 * cent + sizeof(" ����"); i++)
	{
		printf("��");
	}
	printf("��");

	for (i = 0; i < 4; i++)
	{
		gotoxy(MES_LEFT, MES_UP + 1 + i);
		printf("��");
		for(j = 0; j < 2 * cent + sizeof(" ����"); j++)
		{
			printf("  ");
		}
		printf("��");
	}

	gotoxy(MES_LEFT, MES_UP + i + 1);
	printf("��");
	for (i = 0; i < 2 * cent + sizeof(" ����"); i++)
	{
		printf("��");
	}
	printf("��");

	gotoxy(MES_LEFT + cent + sizeof(" ����"), MES_UP + 2);
	printf("%s ����",str);
}

void ShowMessage2(char *str)
{
	int i;
	int j;
	int cent = strlen(str) / 2;

	gotoxy(MES_LEFT, MES_UP);
	printf("��");
	for (i = 0; i < 2 * cent; i++)
	{
		printf("��");
	}
	printf("��");

	for (i = 0; i < 4; i++)
	{
		gotoxy(MES_LEFT, MES_UP + 1 + i);
		printf("��");
		for(j = 0; j < 2 * cent; j++)
		{
			printf("  ");
		}
		printf("��");
	}

	gotoxy(MES_LEFT, MES_UP + i + 1);
	printf("��");
	for (i = 0; i < 2 * cent; i++)
	{
		printf("��");
	}
	printf("��");

	gotoxy(MES_LEFT + cent, MES_UP + 2);
	printf("%s",str);
}

void DrawBigBox(int size, int num)
{ // size:���� �� ���ڿ��� ����. num : ���ڿ����� ����
	int i;
	int j;

	gotoxy(BOX_LEFT - 4, BOX_UP - 2);
	printf("��");
	for (i = 0; i < size / 2 + 12; i++)
	{ // i�� size / 2 +12���� ���°� �����ϴ�.
		printf("��");
	}
	printf("��");

	for (i = BOX_UP - 1; i < BOX_UP + num * 4 - 1; i++)
	{
		gotoxy(BOX_LEFT - 4, i);
		printf("��");

		for (j = 0; j < size / 2 + 12; j++)
		{
			printf("  ");
		}
		printf("��");
	}
	gotoxy(BOX_LEFT - 4, i);
	printf("��");
	for (i = 0; i < size / 2 + 12; i++)
	{
		printf("��");
	}
	printf("��");
}


int SelectSquare(char *str[], int num)
{
	int i;
	int input;
	int x, y;
	int pos = 2;

	x = BOX_LEFT; 
	y = BOX_UP;

	gotoxy(x + 2, y);
	printf("%s", str[0]); // str[0]�� ������ title�̴�.(��������)

	for (i = 1; i < num; i++)
	{
		gotoxy(x + 2, y + 4 * i);
		printf("%s", str[i]);
	}

	PrintBox(str[pos - 1], pos);

	while (1)
	{
		input = getch();

		if (input == 0xE0 || 0x00)
		{
			input = getch();

			switch (input)
			{
			case UP:
				if (pos > 2)
				{
					DeleteBox(str[pos - 1], pos);
					y -= 4;
					pos--;
					PrintBox(str[pos - 1], pos);
				}
				break;
			case DOWN:
				if (pos < num)
				{
					DeleteBox(str[pos - 1], pos);
					y += 4;
					pos++;
					PrintBox(str[pos - 1], pos);
				}
				break;
			}
		}
		else
		{
			switch (input)
			{
			case ENTER:
				return pos - 1;
			}
		}
	}

}

void PrintBox(char *str, int num)
{
	int i;
	int len = strlen(str);

	gotoxy(BOX_LEFT, BOX_UP + (num - 1) * 4 - 1);
	printf("��");
	for (i = 0; i < len / 2 + 1; i++)
	{
		printf("��");
	}
	printf("��");
	gotoxy(BOX_LEFT, BOX_UP + (num - 1) * 4);
	printf("��");
	for (i = 0; i < len / 2 + 1; i++)
	{
		printf("  ");
	}
	printf("��");
	gotoxy(BOX_LEFT, BOX_UP + (num - 1) * 4 + 1);
	printf("��");
	for (i = 0; i < len / 2 + 1/*str[i] != '\0'*/; i++)
	{
		printf("��");
	}
	printf("��");
	gotoxy(BOX_LEFT + 2, BOX_UP + (num - 1) * 4);
	printf(str);
	
}

void DeleteBox(char *str, int num)
{
	int i;
	int len = strlen(str);

	if (len < 4)
	{
		len = 4;
	}

	gotoxy(BOX_LEFT, BOX_UP + (num - 1) * 4 - 1);
	for (i = 0; i < len / 2 + 4; i++)
	{
		printf("  ");
	}
	gotoxy(BOX_LEFT, BOX_UP + (num - 1) * 4);
	for (i = 0; i < len / 2 + 4; i++)
	{
		printf("  ");
	}
	gotoxy(BOX_LEFT, BOX_UP + (num - 1) * 4 + 1);
	for (i = 0; i < len / 2 + 4; i++)
	{
		printf("  ");
	}
	gotoxy(BOX_LEFT + 2, BOX_UP + (num - 1) * 4);
	printf(str);
}