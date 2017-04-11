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
		Flag_Init(mp + i); // �� �ϳ��� �Ѱ��ش�.
		Monster_Init(mp + i); // �� �ϳ��� �Ѱ��ش�.
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

	treasuremap = rand() % MAP_NUM; // ���� �ִ� ����.
	mp[treasuremap].pMap[mp[treasuremap].arFlag[MONSTER_NUM].y]
		[mp[treasuremap].arFlag[MONSTER_NUM].x / 2] = 2;

	mp[0].onoff = TRUE;
}

void Monster_Init(Map *mp)
{ // �� �Լ��� �� �ϳ��� ���ڷ� �޴´�.
	int i;
	int j;

	for (i = 0; i < MONSTER_NUM; i++)
	{
		mp->arMonster[i].isMoved = FALSE; // ó������ isMoved�� TRUE�� �ؾ� ���δ�.
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
{ // �� �Լ��� �� �ϳ��� ���ڷ� �޴´�. �������.
	//���� ��� x, y�� 0���� �ʱ�ȭ����.
	int i;
	int j;
	int check;

	for (i = 0; i < FLAG_NUM; i++)
	{ // ���� x, y�� 0���� �ʱ�ȭ.
		mp->arFlag[i].x = 0;
		mp->arFlag[i].y = 0;
	}

	for (i = 0; i < FLAG_NUM; i++)
	{
		check = 0;
		mp->arFlag[i].x = ((rand() % (mp->width - 1)) + 1) * 2;
		mp->arFlag[i].y = (rand() % (mp->height - 1)) + 1; // ���� �� �����϶�.

		if (mp->pMap[mp->arFlag[i].y][mp->arFlag[i].x / 2] > 0)
		{
			i--;
			continue;
		}
		if (mp->arFlag[i].x == 2 && mp->arFlag[i].y == 1)
		{ // ��� ���� 2,1�� 
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
		} // flag_enable, display ��� FALSE�� �ʱ�ȭ�Ѵ�.
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
	Player_Print(pp, oldx, oldy); // �Ѿ��� ��� ��������? Player_Move����.

	return;
}

void Player_Print(Player *pp, int *oldx, int *oldy)
{ // static ������ �ٸ��� �����.

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
		pp->bulletinterval = 0; //�Լ��� �� �� ȣ���� �� ���� �Ѿ��� ������Ʈ�Ѵ�.
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
	// Ű �Է¹ޱ�
	if ((GetKeyState(VK_UP) & 0x8000) && (mp[nowMap].pMap[pp->y - 1][pp->x / 2] != 1))
	{ // ���� �Ȱ��� �ȴ�. ���Ͽ� ������ �Ѿ�� Map_Change���� �˻��Ѵ�.
		pp->y--;
		pp->dir = 0;
		pp->display = FALSE;
	}
	if (GetKeyState(VK_DOWN) & 0x8000 && (mp[nowMap].pMap[pp->y + 1][pp->x / 2] != 1))
	{ // ������ ���� 1�� �ƴϸ� �װ����� ��������.
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
	//Ű �Է¹ޱ� ��
}

void Player_Change(Player *pp, Map *mp)
{ //�� ��θ� Map_Change��.
	int nowMap;
	int i;

	for (i = 0; i < MAP_NUM; i++)
	{
		if (mp[i].onoff)
		{
			nowMap = i;
			break;
		}
	} // ���� �ٲ�� �� ��ġ�� �ٲ�� �Ѵ�. �̰��� Map_Change���� ������
	// ���⼭ �ϴ� ���� �������� �Ǵ�.

}

void Monster_Update(Player *pp, Map *mp, int *monster_Frame, int *monster_FrameF)
{ // &player, arMap
	Monster_Move(pp, mp, monster_Frame, monster_FrameF);
	Monster_Change(pp, mp);
	Monster_Print(mp);

	return;
}

void Monster_Print(Map *mp)
{ // ������ �ܻ��� ��� ����°�.
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
	// ���� ���� ���Ѵ�.

	for (i = 0; i < MONSTER_NUM; i++) // i�� ������ �� ���ƶ�.
	{ // �������� �� ����ش�. �׷� ó���� ������ ���� ��� �ϴ°�?
		if (mp[nowMap].arMonster[i].monster_enable)
		{
			if (!(mp[nowMap].arMonster[i].display)) // display�� false�� ���� ����ָ� �Ǵ� �Ŵ�.
			{ // monster_enable�� 1�ε� display�� 0�̸� �Ⱥ��̴� ���̹Ƿ� ����ش�.
				if (mp[nowMap].arMonster[i].delay <= 0) // delay�� 0�̸� isMoved�� TRUE��.
				{// delay�� 0�̸� ����ش�. �ƴϸ� �����̸� ���ҽ�Ų��.
					if (mp[nowMap].arMonster[i].isMoved)
					{ // display�� 0���� ���� ���� isMoved�� TRUE�� �ؾ� �Ѵ�.
						gotoxy(mp[nowMap].arMonster[i].x, mp[nowMap].arMonster[i].y);
						printf(MONSTER_FIGURE);

						//// ������ ��ġ�� ����Ѵ�.
						//gotoxy(70, 10 + i * 2);
						//printf("mon%d : %d, %d", i, mp[nowMap].arMonster[i].x,
						//	mp[nowMap].arMonster[i].y);

						mp[nowMap].arMonster[i].display = TRUE;
						mp[nowMap].arMonster[i].isMoved = FALSE;
						// display�� 0�� �Ǵ� ���� ���Ͱ� ������� ��.
						// ->���Ͱ� �׾��� �� Ȥ�� ���� �ٲ���� ��.
						//mp[nowMap].arMonster[i].display = 1;
					}
				}
				else
				{ // ������ ���Ҵ� Monster_Change���� ���ִ� �� �´°� �´�.
					(mp[nowMap].arMonster[i].delay)--; // display�� 0�ε� delay�� �ȵǾ� ������
					if (mp[nowMap].arMonster[i].delay <= 0) // delay�� �����.
					{ // delay�� 0�̸� ������ isMoved�� true�� ����� �ϴ°�?
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
	{ // ���Ͱ� �����δ�.
		*monster_Frame = 0;
		monster_position(pp, mp);
	}
}

void Monster_Change(Player *pp, Map *mp)
{ // ������ ������ ���⼭ �����Ѵ�.
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
{ // �ʺ��� ����Ʈ�ؾ�. (system("cls")�� ��������Ƿ�.)
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
	{ // nowMap�� ã�� nowMap�� display�� �˻��Ѵ�.
		system("cls");

		for (i = 0; i < mp[nowMap].height; i++)
		{
			printf("%s\n", mp[nowMap].cMap[i]);
		}
		mp[nowMap].display = TRUE;
	}
}

void Map_Change(Player *pp, Map *mp)
{// ���⼭ �÷��̾ �����̸� ���� �ٲ۴�.
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
	{ // ���� �ٲ�� �ؾ� �� ��� �͵��� ���⼭ �ؾ� �Ѵ�.
		int tempx = pp->x;
		 // ���� ��� ���� ���� ��� 0���� �����.
		/////////////////////////
		mp[nowMap].onoff = FALSE;
		mp[ mp[nowMap].pMap[pp->y][pp->x / 2] / 10000 - 1 ].onoff = TRUE;
		mp[nowMap].display = FALSE;
		mp[ mp[nowMap].pMap[pp->y][pp->x / 2] / 10000 - 1 ].display = FALSE;
		////////////////////////////
		// ���� �ٲ���� �� �ٲ�� ���� ����.
		///////////////////////
		pp->display = FALSE;
		pp->MapChanged = TRUE;
		///////////////////////
		// ���� �ٲ���� �� �ٲ�� �÷��̾��� ����.
		for (i = 0, j = 0; i < FLAG_NUM || j < MONSTER_NUM; i++ ,j++)
		{ // �� �� �÷��׵� 0���� �������� ���� �� �浵 0����?
			if (j >= MONSTER_NUM) j--;

			/////////////////////////
			if (!mp[nowMap].arFlag[i].flag_enable)
			{
				mp[nowMap].arFlag[i].display = FALSE;
				mp[mp[nowMap].pMap[pp->y][pp->x / 2] / 10000 - 1].arFlag[i].display = FALSE;
			}
			//////////////////////////
			// ���� �ٲ���� �� �ٲ�� �÷����� ����.
			/////////////////////////
			if (mp[nowMap].arMonster[j].monster_enable)
			{
				mp[nowMap].arMonster[j].display = FALSE;
				mp[nowMap].arMonster[j].isMoved = TRUE;
			}
			// ��� ������ isMoved�� TRUE�� �ٲٴ� �� �ƴ϶�
			// monster_enable�� ���͸� �ٲ��.
			////////////////////////
			// ���� �ٲ���� �� �ٲ�� ������ ����.
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
	{ // ����� Flag_Change�� ���� ������ ���̴� �����ΰ�?
		if (!mp[nowMap].arFlag[i].flag_enable)
		{ // flag_enable�� Ư���ϰԵ� false�� �� ����ش�.
			if (!mp[nowMap].arFlag[i].display)
			{ //���� �÷��� ���� ���� �ʾҴµ�(flag_enable == 0) ǥ�õ� �ȵ��ִٸ�(display == 0)
				gotoxy(mp[nowMap].arFlag[i].x, mp[nowMap].arFlag[i].y); // ���� ǥ���ϰ� display�� 1�� ������.
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