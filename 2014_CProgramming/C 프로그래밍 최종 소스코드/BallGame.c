#include "Data.h"

BOOL BallGame()
{
	char *GameNum;
	char *arInputNum;
	int count; // count는 1부터 시작
	char **arFrame;
	int result;
	BOOL cn; // 제어 변수
	BOOL WinLose;

	GameNum = NULL;
	arInputNum = NULL;
	count = 1;
	arFrame = NULL;
	cn = FALSE;
	WinLose = FALSE;

	displayCursor();
	Setting(&GameNum, &arInputNum);
	Interface(&arFrame);

	while (201312845)
	{
		result = 0;
		InputNum(&GameNum, &arInputNum, &count, &result);
		cn = Result(GameNum, &result, &count, &WinLose);
		if (cn == TRUE)
		{
			break;
		}
	}

	removeCursor();

	Destroy(&GameNum, &arInputNum, &arFrame);

	return WinLose;
}

void NumCheck(char **gnp, char **ipnp, int *rp)
{
	int i;
	int j;

	i = 0;
	j = 0;

	for (i = 0; i < NUMSIZE; i++)
	{
		if ((*gnp)[i] == (*ipnp)[i])
		{
			*rp += 10;
		}
		else
		{
			for (j = 0; j < NUMSIZE; j++)
			{
				if ((*gnp)[i] == (*ipnp)[j])
				{
					(*rp)++;
					break;
				}
			}
		}
	}
}

BOOL Result(char *gnp, int *rp, int *count, BOOL *WinLose)
{
	int i; 
	
	i = 0;

	gotoxy(MAX_LEFT + 40, MAX_UP + 5 + *count - 2);

	if (*rp == (10 * NUMSIZE))
	{
		printf("정답!");
		*WinLose = TRUE;
		return TRUE;
	}
	else if (*count == BALLGAME_ENDNUM)
	{
		printf("게임 실패! 정답은 ");
		for (i = 0; i < NUMSIZE; i++)
		{
			printf("%c ", gnp[i]);
		}
		printf("입니다!");
		*WinLose = FALSE;
		return TRUE;
	}

	printf("%d STRIKE %d BALL!", *rp / 10, *rp % 10);
	return FALSE;
}

void Interface(char ***arfp)
{
	int i;
	int j; 
	
	j = 0;
	i = 0;

	*arfp = (char **)calloc(sizeof(char *), 3);
	assert(arfp != NULL);

	for (i = 0; i < 3; i++)
	{
		char *arTemp = (char *)calloc(ROW_SIZE / 2 + 1, sizeof(D9));
		assert(arTemp != NULL);

		switch (i)
		{
		case 0:
			strcat(arTemp, D1);
			for (j = 0; j < ROW_SIZE / 2 - 2; j++)
			{
				strcat(arTemp, D10);
			}
			strcat(arTemp, D3);
			break;
		case 1:
			strcat(arTemp, D9);
			for (j = 0; j < ROW_SIZE / 2 - 2; j++)
			{
				strcat(arTemp, "  ");
			}
			strcat(arTemp, D9);
			break;
		case 2:
			strcat(arTemp, D2);
			for (j = 0; j < ROW_SIZE / 2 - 2; j++)
			{
				strcat(arTemp, D10);
			}
			strcat(arTemp, D4);
			break;
		}
		(*arfp)[i] = (char *)calloc(ROW_SIZE / 2 + 1, sizeof(D9));
		assert((*arfp)[i] != NULL);
		strcpy((*arfp)[i], arTemp);
		free(arTemp);
	}

	gotoxy(MAX_LEFT, MAX_UP);
	printf((*arfp)[0]);
	for (i = 0; i < COL_SIZE - 1; i++)
	{
		gotoxy(MAX_LEFT, MAX_UP + 1 + i);
		printf((*arfp)[1]);
	}
	gotoxy(MAX_LEFT, MAX_UP + COL_SIZE);
	printf((*arfp)[2]);

	return;
}

void InputNum(char **gnp, char **ipnp, int *count, int *rp)
{
	int checkNum, InputCount = 0;
	int i;

	while (201312845)
	{
		i = 0;

		gotoxy(MAX_LEFT + 10, MAX_UP + 5 + *count - 1);
		printf("#%d번째 도전 : ", *count);
		gotoxy(MAX_LEFT + 10 + sizeof("#%d번째 도전 : "), MAX_UP + 5 + *count - 1);

		while ((*ipnp)[i] != '\0')
		{
			printf("%c ", (*ipnp)[i]);
			i++;
		}
		i = 0;
		
		if (InputCount == NUMSIZE)
		{
			NumCheck(gnp, ipnp, rp);
			(*count)++;
			(*ipnp)[0] = '\0';
			//return TRUE;
			break;
		}

		checkNum = getch();

		if (checkNum <= '9' && checkNum >= '0')
		{
			(*ipnp)[InputCount++] = checkNum;
			(*ipnp)[InputCount] = '\0';
			//i++;
		}
		else if (checkNum == 0x00 || 0xE0)
		{
			//checkNum = getch();

			switch (checkNum)
			{
			case BACKSPACE:
				gotoxy(MAX_LEFT + 10 +  sizeof("#%d번째 도전 : "),
					MAX_UP + 5 + *count - 1);
				printf("                   ");
				//i--;
				if (InputCount > 0)
				{
					(*ipnp)[--InputCount] = '\0';
				}
				break;
			}
		}
	}
}

void Setting(char **gnp, char **ipnp)
{
	int *arCheck = (int *)calloc(sizeof(int), 9);
	int i; 
	i = 0;
	*gnp = (char *)calloc(sizeof(char), NUMSIZE + 1);
	assert(gnp != NULL);
	*ipnp = (char *)calloc(sizeof(char), NUMSIZE + 1);
	assert(ipnp != NULL);
	rand();

	for (i = 0; i < NUMSIZE; i++)
	{
		(*gnp)[i] = rand() % 9 + 1 + '0';

		if (arCheck[(*gnp)[i] - '0' - 1] == 1)
		{ 
			i--;
			continue;
		}

		arCheck[(*gnp)[i] - '0' - 1] = 1;
	}
	
	free(arCheck);
	(*gnp)[NUMSIZE] = '\0';
	return;
}

void Destroy(char **gnp, char **ipnp, char ***arfp)
{
	int i; 
	
	i = 0;

	free(*gnp);
	free(*ipnp);

	for (i = 0; i < 3; i++)
	{
		free((*arfp)[i]);
	}

	return;
}
