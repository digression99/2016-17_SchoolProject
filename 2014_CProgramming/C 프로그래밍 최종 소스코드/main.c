#include "Data.h"

void Init(Player *pp, Map *mp)
{
	Player_Init(pp);
	Map_Init(mp);
	return;
}

void Map_Init(Map *mp)
{
	int i;
	int j;
	int k;
	int treasuremap;

	rand();

	for (i = 0; i < MAP_NUM; i++)
	{
		Map_SingleMapInit(mp + i, i);
		Map_CharMapInit(mp + i);
		Flag_Init(mp + i); // 맵 하나를 넘겨준다.
		Monster_Init(mp + i); // 맵 하나를 넘겨준다.
	}
	
	for (i = 0; i < MAP_NUM; i++)
	{
		for (j = 0; j < mp[i].height; j++)
		{
			for (k = 0; k < mp[i].width; k++)
			{
				if (mp[i].pMap[j][k] == 2)
				{
					mp[i].pMap[j][k] = 0;
					break;
				}
			}
		}
	}

	treasuremap = rand() % MAP_NUM; // 보물 넣는 로직.
	mp[treasuremap].pMap[mp[treasuremap].arFlag[MONSTER_NUM].y]
		[mp[treasuremap].arFlag[MONSTER_NUM].x / 2] = 2;

	mp[0].onoff = TRUE;
}

void Monster_Init(Map *mp)
{ // 이 함수도 맵 하나를 인자로 받는다.
	int i;
	int j;

	for (i = 0; i < MONSTER_NUM; i++)
	{
		mp->arMonster[i].isMoved = FALSE; // 처음에는 isMoved를 TRUE로 해야 보인다.
		mp->arMonster[i].display = FALSE;
		mp->arMonster[i].monster_enable = FALSE;
		mp->arMonster[i].delay = 100;
		mp->arMonster[i].hp = 1;

		for (j = 0; j < MONSTER_BULLET_NUM; j++)
		{
			mp->arMonster[i].xybullet[j][0] = 0;
			mp->arMonster[i].xybullet[j][1] = 0;
		}
		mp->arMonster[i].x = mp->arFlag[i].x;
		mp->arMonster[i].y = mp->arFlag[i].y;
	}

	return;
}

void Flag_Init(Map *mp)
{ // 이 함수는 맵 하나를 인자로 받는다. 명심하자.
	//먼저 모든 x, y를 0으로 초기화하자.
	int i;
	int j;
	int check;

	for (i = 0; i < FLAG_NUM; i++)
	{ // 먼저 x, y를 0으로 초기화.
		mp->arFlag[i].x = 0;
		mp->arFlag[i].y = 0;
	}

	for (i = 0; i < FLAG_NUM; i++)
	{
		check = 0;
		mp->arFlag[i].x = ((rand() % (mp->width - 1)) + 1) * 2;
		mp->arFlag[i].y = (rand() % (mp->height - 1)) + 1; // 여기 식 주의하라.

		if (mp->pMap[mp->arFlag[i].y][mp->arFlag[i].x / 2] > 0)
		{
			i--;
			continue;
		}
		if (mp->arFlag[i].x == 2 && mp->arFlag[i].y == 1)
		{ // 모든 맵의 2,1이 
			i--;
			continue;
		}

		for (j = i - 1; j >= 0; j--)
		{
			if (mp->arFlag[j].x == mp->arFlag[i].x && mp->arFlag[j].y == mp->arFlag[i].y)
			{
				i--;
				check = 1;
				break;
			}
		} // flag_enable, display 모두 FALSE로 초기화한다.
		if (check == 1)
		{
			continue;
		}
		mp->arFlag[i].flag_enable = mp->arFlag[i].display = FALSE; 
	}
}

void Player_Init(Player *player)
{
	int i;
	player->interval = 0;
	player->damage = 1;
	player->x = 2;
	player->y = 1;
	player->health = 100;
	player->bNum = 0;
	player->dir = 3;
	player->shootdelay = 0;
	player->bulletinterval = 0;
	player->display = FALSE;
	player->MapChanged = FALSE;

	for (i = 0; i<5; i++)
	{
		player->bullet[i].range = 0;
	}
}

void Player_Update(Player *pp, Map *mp, int *oldx, int *oldy)
{ // &player, arMap
	Player_Move(pp, mp);
	Player_Change(pp, mp);
	Player_Print(pp, oldx, oldy); // 총알을 어디서 관리하지? Player_Move에서.

	return;
}

void Player_Print(Player *pp, int *oldx, int *oldy)
{ // static 변수와 다르면 지운다.

	if (!(pp->display))
	{
		if (pp->MapChanged)
		{
			pp->MapChanged = FALSE;
		}
		else
		{
			if (*oldx != pp->x || *oldy != pp->y)
			{
				gotoxy(*oldx, *oldy);
				printf("  ");
			}
		}
		*oldx = pp->x;
		*oldy = pp->y;
		gotoxy(pp->x, pp->y);
		printf(CHARACTER_FIGURE);
		pp->display = TRUE;
	}
}

void Player_Move(Player *pp, Map *mp)
{
	int nowMap;
	int i;

	for (i = 0; i < MAP_NUM; i++)
	{
		if (mp[i].onoff == 1)
		{
			nowMap = i;
			break;
		}
	}
	pp->interval++;
	pp->bulletinterval++;

	if (pp->bulletinterval >= 2)
	{
		Player_Bullet_Update(pp, mp);
		pp->bulletinterval = 0; //함수를 두 번 호출할 때 마다 총알을 업데이트한다.
	}
	if (pp->interval < 5)
	{
		return;
	}
	else
	{
		pp->interval = 0;
	}
	pp->shootdelay++;

	/////////////////////////////////
	// 키 입력받기
	if ((GetKeyState(VK_UP) & 0x8000) && (mp[nowMap].pMap[pp->y - 1][pp->x / 2] != 1))
	{ // 벽만 안가면 된다. 만일에 문으로 넘어가면 Map_Change에서 검사한다.
		pp->y--;
		pp->dir = 0;
		pp->display = FALSE;
	}
	if (GetKeyState(VK_DOWN) & 0x8000 && (mp[nowMap].pMap[pp->y + 1][pp->x / 2] != 1))
	{ // 움직인 곳이 1이 아니면 그곳으로 움직여라.
		pp->dir = 1;
		pp->y++;
		pp->display = FALSE;
	}
	if (GetKeyState(VK_LEFT) & 0x8000 && (mp[nowMap].pMap[pp->y][(pp->x - 2) / 2] != 1))
	{
		pp->dir = 2;
		pp->x -= 2;
		pp->display = FALSE;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000 && (mp[nowMap].pMap[pp->y][(pp->x + 2) / 2] != 1))
	{
		pp->dir = 3;
		pp->x += 2;
		pp->display = FALSE;
	}
	////////////////////////////////
	//키 입력받기 끝
}

void Player_Change(Player *pp, Map *mp)
{ //이 모두를 Map_Change로.
	int nowMap;
	int i;

	for (i = 0; i < MAP_NUM; i++)
	{
		if (mp[i].onoff)
		{
			nowMap = i;
			break;
		}
	} // 맵이 바뀌면 내 위치가 바뀌여아 한다. 이것은 Map_Change에서 하지만
	// 여기서 하는 것이 논리적으로 옳다.

}

void Monster_Update(Player *pp, Map *mp, int *monster_Frame, int *monster_FrameF)
{ // &player, arMap
	Monster_Move(pp, mp, monster_Frame, monster_FrameF);
	Monster_Change(pp, mp);
	Monster_Print(mp);

	return;
}

void Monster_Print(Map *mp)
{ // 몬스터의 잔상은 어디서 지우는가.
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
	////////////////////////////
	// 현재 맵을 구한다.

	for (i = 0; i < MONSTER_NUM; i++) // i의 범위를 잘 보아라.
	{ // 움직였을 때 찍어준다. 그럼 처음에 등장할 때는 어떻게 하는가?
		if (mp[nowMap].arMonster[i].monster_enable)
		{
			if (!(mp[nowMap].arMonster[i].display)) // display가 false일 때만 찍어주면 되는 거다.
			{ // monster_enable은 1인데 display가 0이면 안보이는 것이므로 찍어준다.
				if (mp[nowMap].arMonster[i].delay <= 0) // delay가 0이면 isMoved를 TRUE로.
				{// delay가 0이면 찍어준다. 아니면 딜레이를 감소시킨다.
					if (mp[nowMap].arMonster[i].isMoved)
					{ // display를 0으로 만들 때는 isMoved를 TRUE로 해야 한다.
						gotoxy(mp[nowMap].arMonster[i].x, mp[nowMap].arMonster[i].y);
						printf(MONSTER_FIGURE);

						//// 몬스터의 위치를 출력한다.
						//gotoxy(70, 10 + i * 2);
						//printf("mon%d : %d, %d", i, mp[nowMap].arMonster[i].x,
						//	mp[nowMap].arMonster[i].y);

						mp[nowMap].arMonster[i].display = TRUE;
						mp[nowMap].arMonster[i].isMoved = FALSE;
						// display가 0로 되는 것은 몬스터가 사라졌을 때.
						// ->몬스터가 죽었을 때 혹은 맵이 바뀌었을 때.
						//mp[nowMap].arMonster[i].display = 1;
					}
				}
				else
				{ // 딜레이 감소는 Monster_Change에서 해주는 게 맞는가 맞다.
					(mp[nowMap].arMonster[i].delay)--; // display가 0인데 delay가 안되어 있으면
					if (mp[nowMap].arMonster[i].delay <= 0) // delay를 빼줘라.
					{ // delay가 0이면 무조건 isMoved를 true로 해줘야 하는가?
						mp[nowMap].arMonster[i].isMoved = TRUE;
						mp[nowMap].arMonster[i].display = FALSE;
					}
				}
			}
		}
	}
}

void Monster_Move(Player *pp, Map *mp, int *monster_Frame, int *monster_FrameF)
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

	if (*monster_Frame <= *monster_FrameF)
	{
		(*monster_Frame)++;
	}
	else
	{ // 몬스터가 움직인다.
		*monster_Frame = 0;
		monster_position(pp, mp);
	}
}

void Monster_Change(Player *pp, Map *mp)
{ // 몬스터의 등장을 여기서 조작한다.
	int nowMap;
	int i;

	for (i = 0; i < MAP_NUM; i++)
	{
		if (mp[i].onoff)
		{
			nowMap = i;
		}
	}
}

void Map_Update(Player *pp, Map *mp)
{ // &player, arMap
	Map_Change(pp, mp);
	Map_Print(mp);
}

void Map_Print(Map *mp)
{ // 맵부터 프린트해야. (system("cls")가 들어있으므로.)
	int nowMap;
	int i;
	//int j;

	for (i = 0; i < MAP_NUM; i++)
	{
		if (mp[i].onoff)
		{
			nowMap = i;
			break;
		}
	}

	if (!mp[nowMap].display)
	{ // nowMap을 찾고 nowMap의 display를 검사한다.
		system("cls");

		for (i = 0; i < mp[nowMap].height; i++)
		{
			printf("%s\n", mp[nowMap].cMap[i]);
		}
		mp[nowMap].display = TRUE;
	}
}

void Map_Change(Player *pp, Map *mp)
{// 여기서 플레이어가 움직이면 맵을 바꾼다.
	int nowMap;
	int i;
	int j;

	for (i = 0; i < MAP_NUM; i++)
	{
		if (mp[i].onoff)
		{
			nowMap = i;
			break;
		}
	}

	if (mp[nowMap].pMap[pp->y][pp->x / 2] >= 10000)
	{ // 맵이 바뀌면 해야 할 모든 것들을 여기서 해야 한다.
		int tempx = pp->x;
		 // 현재 방과 다음 방을 모두 0으로 만든다.
		/////////////////////////
		mp[nowMap].onoff = FALSE;
		mp[ mp[nowMap].pMap[pp->y][pp->x / 2] / 10000 - 1 ].onoff = TRUE;
		mp[nowMap].display = FALSE;
		mp[ mp[nowMap].pMap[pp->y][pp->x / 2] / 10000 - 1 ].display = FALSE;
		////////////////////////////
		// 맵이 바뀌었을 때 바뀌는 맵의 정보.
		///////////////////////
		pp->display = FALSE;
		pp->MapChanged = TRUE;
		///////////////////////
		// 맵이 바뀌었을 때 바뀌는 플레이어의 정보.
		for (i = 0, j = 0; i < FLAG_NUM || j < MONSTER_NUM; i++ ,j++)
		{ // 전 방 플래그도 0으로 만들지만 새로 들어갈 방도 0으로?
			if (j >= MONSTER_NUM) j--;

			/////////////////////////
			if (!mp[nowMap].arFlag[i].flag_enable)
			{
				mp[nowMap].arFlag[i].display = FALSE;
				mp[mp[nowMap].pMap[pp->y][pp->x / 2] / 10000 - 1].arFlag[i].display = FALSE;
			}
			//////////////////////////
			// 맵이 바뀌었을 때 바뀌는 플래그의 정보.
			/////////////////////////
			if (mp[nowMap].arMonster[j].monster_enable)
			{
				mp[nowMap].arMonster[j].display = FALSE;
				mp[nowMap].arMonster[j].isMoved = TRUE;
			}
			// 모든 몬스터의 isMoved를 TRUE로 바꾸는 게 아니라
			// monster_enable된 몬스터만 바꿔라.
			////////////////////////
			// 맵이 바뀌었을 때 바뀌는 몬스터의 정보.
		}
		pp->x = mp[nowMap].pMap[pp->y][pp->x / 2] / 100 % 100;
		pp->y = mp[nowMap].pMap[pp->y][tempx / 2] % 100;
	}
}

void Flag_Update(Player *pp, Map *mp)
{
	Flag_Print(mp);
	Flag_Change(pp, mp);
}

void Flag_Print(Map *mp)
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

	for (i = 0; i < FLAG_NUM; i++)
	{ // 여기와 Flag_Change의 같은 로직의 차이는 무엇인가?
		if (!mp[nowMap].arFlag[i].flag_enable)
		{ // flag_enable은 특이하게도 false일 때 찍어준다.
			if (!mp[nowMap].arFlag[i].display)
			{ //아직 플래그 위에 가지 않았는데(flag_enable == 0) 표시도 안되있다면(display == 0)
				gotoxy(mp[nowMap].arFlag[i].x, mp[nowMap].arFlag[i].y); // 가서 표시하고 display를 1로 만들어라.
				printf(FLAG_FIGURE);
				mp[nowMap].arFlag[i].display = TRUE;
			}
		}
	}
}

void Flag_Change(Player *pp, Map *mp)
{ // pp, mp
	int nowMap;
	int i;
	//int j;

	for (i = 0; i < MAP_NUM; i++)
	{
		if (mp[i].onoff)
		{
			nowMap = i;
			break;
		}
	}
	for (i = 0; i < FLAG_NUM; i++)
	{
		if ((mp[nowMap].arFlag[i].x == pp->x) && (mp[nowMap].arFlag[i].y == pp->y))
		{
			if (!(mp[nowMap].arFlag[i].flag_enable))
			{
				mp[nowMap].arFlag[i].flag_enable = TRUE;
				if (i <= MONSTER_NUM)
				{
					if (!(mp[nowMap].arMonster[i].monster_enable))
					{
						mp[nowMap].arMonster[i].monster_enable = TRUE;
					}
				}
			}
		}
	}
}