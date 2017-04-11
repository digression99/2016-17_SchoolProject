#include "Data.h"

int cursor_case(int x)
{
	switch (x)
	{
	case 0: x = 72;
		break;
	case 1: x = 75;
		break;
	case 2: x = 77;
		break;
	case 3: x = 80;
		break;
	default: x = 0;
	} // default는 필요 없을듯.
	return x;
}

int Distance(const int characterX, const int characterY, Monster *mp)
{
	double calcX = abs(characterX - (mp->x));
	double calcY = abs(characterY - (mp->x));

	return (int)(sqrt(pow(calcX, 2) + pow(calcY, 2)));
}
////////////////////////////////////////////////9.캐릭터를 향한 몬스터의 움직임
void monster_position(Player *pp, Map *mp)
{
	int nowMap;
	int i;
	for (i = 0; i < MAP_NUM; i++)
	{
		if (mp[i].onoff)
		{
			nowMap = i;
		}
	}

	for (i = 0; i < MONSTER_NUM; i++)
	{
		if (mp[nowMap].arMonster[i].monster_enable)
		{ // display와 isMoved를 조절해야. isMoved가 드디어 등장할 때 조절되는 것.
			if (mp[nowMap].arMonster[i].display)
			{ // display가 FALSE이면 움직이지 않아야.
				if (mp[nowMap].arMonster[i].delay <= 0)
				{
					if (mp[nowMap].arMonster[i].isMoved == FALSE)
					{
						gotoxy(mp[nowMap].arMonster[i].x, mp[nowMap].arMonster[i].y);
						printf("  ");

						if (Distance(pp->x, pp->y, &mp[nowMap].arMonster[i]) <= MONSTER_BETWEEN)
						{ // 벽이 있으면 못가야 한다. 그것은 toward에서. toward 수정해야. 몬스터의 움직이려는 위치는 어떻게 정하는가?
							toward(pp, mp, i); // x와 y의 차로 정한다.
						}
						else
						{
							small_m_movement(mp, i, cursor_case(rand() % 4));
						}

						mp[nowMap].arMonster[i].isMoved = TRUE;
						mp[nowMap].arMonster[i].display = FALSE;
					}
				}
			}
		} // isMoved가 TRUE이면 움직여야 한다.
	}
}

int calcDif(int pnum, int mnum, int xy)
{
	int temp;
	if (xy == 1)
	{
		if (pnum - mnum < 0)
		{
			temp = -2;
		}
		else if (pnum - mnum > 0)
		{
			temp = 2;
		}
		else
		{
			temp = 0;
		}
	}
	else
	{
		if (pnum - mnum < 0)
		{
			temp = -1;
		}
		else if (pnum - mnum > 0)
		{
			temp = 1;
		}
		else
		{
			temp = 0;
		}
	}

	return temp;
}

void toward(Player *pp, Map *mp, int monNum)
{
	int nowMap;
	int resultx, resulty;
	int i;

	 // %2 하면 0 아니면 1 아니면 -1이 나온다. // 아니다. 이상한 값 나온다.
	for (i = 0; i < MAP_NUM; i++)
	{
		if (mp[i].onoff)
		{
			nowMap = i;
			break;
		}
	}
	if (mp[nowMap].pMap[mp[nowMap].arMonster[monNum].y + calcDif(pp->y, mp[nowMap].arMonster[monNum].y, 2)]
		[ (mp[nowMap].arMonster[monNum].x + calcDif(pp->x, mp[nowMap].arMonster[monNum].x, 1)) / 2] > 0)
	{
		return;
	}

	resultx = mp[nowMap].arMonster[monNum].x + calcDif(pp->x, mp[nowMap].arMonster[monNum].x, 1);
	resulty = mp[nowMap].arMonster[monNum].y + calcDif(pp->y, mp[nowMap].arMonster[monNum].y, 2);

	for (i = 0; i < FLAG_NUM; i++)
	{
		if (!(mp[nowMap].arFlag[i].flag_enable))
		{
			if (resultx == mp[nowMap].arFlag[i].x &&
				resulty == mp[nowMap].arFlag[i].y)
			{
				return;
			}
		}
	}

	(mp[nowMap].arMonster[monNum].x) += calcDif(pp->x, mp[nowMap].arMonster[monNum].x, 1);
	(mp[nowMap].arMonster[monNum].y) += calcDif(pp->y, mp[nowMap].arMonster[monNum].y, 2);
}

void small_m_movement(Map *mp, int monNum, int key)
{
	int i;
	int nowMap;
	int oldx;
	int oldy;

	for (i = 0; i < MAP_NUM; i++)
	{
		if (mp[i].onoff)
		{
			nowMap = i;
			break;
		}
	}

	oldx = mp[nowMap].arMonster[monNum].x;
	oldy = mp[nowMap].arMonster[monNum].y;

	switch (key)
	{
	case UP:
		mp[nowMap].arMonster[monNum].y--;
		break;
	case DOWN:
		mp[nowMap].arMonster[monNum].y++;
		break;
	case LEFT:
		mp[nowMap].arMonster[monNum].x -= 2;
		break;
	case RIGHT:
		mp[nowMap].arMonster[monNum].x += 2;
		break;
	}

	if (mp[nowMap].pMap[mp[nowMap].arMonster[monNum].y][mp[nowMap].arMonster[monNum].x / 2] > 0)
	{
		mp[nowMap].arMonster[monNum].x = oldx;
		mp[nowMap].arMonster[monNum].y = oldy;
	}

	for (i = 0; i < FLAG_NUM; i++)
	{
		if (!(mp[nowMap].arFlag[i].flag_enable))
		{
			if (mp[nowMap].arMonster[monNum].y == mp[nowMap].arFlag[i].y &&
				mp[nowMap].arMonster[monNum].x == mp[nowMap].arFlag[i].x)
			{
				mp[nowMap].arMonster[monNum].x = oldx;
				mp[nowMap].arMonster[monNum].y = oldy;
			}
		}
	}
}

int compare(Player *pp, Map *mp, BOOL *key)
{
	int nowMap;
	int i;

	for (i = 0; i < MAP_NUM; i++)
	{
		if (mp[i].onoff)
		{
			nowMap = i;
			break;
		}
	}

	for (i = 0; i < MONSTER_NUM; i++)
	{ // 몬스터와 만났는지를 검사.
		if (mp[nowMap].arMonster[i].x == pp->x && mp[nowMap].arMonster[i].y == pp->y)
		{
			if (mp[nowMap].arMonster[i].monster_enable)
			{
				if (mp[nowMap].arMonster[i].display)
				{
					if (mp[nowMap].arMonster[i].delay <= 0)
					{ // monster_enable, display, delay를 조절하는 것을 통일해야 한다.(Monster_Change에서)
						*key = FALSE;
						return 1;
					}
				}
			}
		}
	}
	if (mp[nowMap].pMap[pp->y][pp->x / 2] == 2)
	{
		*key = TRUE;
		return 1;
	}

	return 0;
}