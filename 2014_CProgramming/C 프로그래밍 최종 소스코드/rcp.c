//
// �ۼ��� : ���Ͻ�
// ���������� ����.
//
//
#include "Data.h"

BOOL Rcp()
{
	char **arFrame = NULL;
	char str[128];
	int count = 0;
	BOOL res;

	sprintf(str, "mode con lines=%d cols=%d", COL_SIZE, ROW_SIZE);
	system(str);
	srand((unsigned)time(NULL));
	rand();

	Interface(&arFrame);

	res = Game(&count);

	gotoxy(MAX_LEFT + 10, MAX_UP + 2);
	if (res == TRUE)
	{
		printf("�¸�!");
		return TRUE;
	}
	else
	{
		printf("�й�!");
		return FALSE;
	}
}

void clear(int x, int y, int mx, int my)
{
	int i;
	int j;
	for (i = y; i < my; i++)
	{
		for (j = x; j < mx; j++)
		{
			gotoxy(j, i);
			printf(" ");
		}
	}

	return;
}

BOOL Game(int *count)
{
	int comRes;
	char str[128];
	int res, res3 = 0;
	BOOL res2 = FALSE;

	removeCursor();

	while (201312845)
	{
		if (*count == GAMENUM || res3 == WINNUM ||
			*count > GAMENUM / 2 && res3 < WINNUM / 2 ||
			*count > (GAMENUM / 2 + 1) && res3 < WINNUM / 2 + 1)
		{
			break;
		}
		
		comRes = rand() % 3 + 1;
		clear(MAX_LEFT + 4, MAX_UP + 3, MAX_LEFT + ROW_SIZE - 2, MAX_UP + 7);

		gotoxy(MAX_LEFT + 5, MAX_UP + 5);
		printf("%d��° : ����, ����, �� �� �ϳ��� ������! : ", *count + 1);
		displayCursor();
		gets(str);
		if (strcmp(str, "����") == 0)
		{
			res = 1;
		}
		else if (strcmp(str, "����") == 0)
		{
			res = 2;
		}
		else if (strcmp(str, "��") == 0)
		{
			res = 3;
		}
		else
		{
			res = 4;
		}
		if (res != 4)
		{
			if (res == comRes)
			{
				gotoxy(MAX_LEFT + 5, MAX_UP + 6);
				printf("�����ϴ�!");
				//res2 = TRUE;
				(*count)++;
				getch();
				continue;
			}
			else
			{
				switch (comRes)
				{
				case 1:
					if (res == 2)
					{
						res2 = TRUE;
						break;
					}
					res2 = FALSE;
					break;
				case 2:
					if (res == 1)
					{
						res2 = FALSE;
						break;
					}
					res2 = TRUE;
					break;
				case 3:
					if (res == 1)
					{
						res2 = TRUE;
						break;
					}
					res2 = FALSE;
					break;
				}
			}
		}
		else
		{
			continue;
		}
		if (res2 == TRUE)
		{
			gotoxy(MAX_LEFT + 5, MAX_UP + 6);
			printf("�̰���ϴ�!");
			res3++;
		}
		else if (res2 == FALSE)
		{
			gotoxy(MAX_LEFT + 5, MAX_UP + 6);
			printf("�����ϴ�!");
		}
		(*count)++;
		getch();
	}
	if (res3 == WINNUM)
	{
		return TRUE;
	}
	return FALSE;
}