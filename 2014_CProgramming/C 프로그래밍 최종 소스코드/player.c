#include "Data.h"

void Player_Shoot(Player *p)
{ // 총알을 초기화하는 것과 같다. Bullet_Init으로.
	p->bNum++;
	if (p->bNum > 4)
	{
		p->bNum = 0;
		return;
	}
	p->bullet[p->bNum].x = p->x;
	p->bullet[p->bNum].y = p->y;
	p->bullet[p->bNum].range = 7;
	p->bullet[p->bNum].dir = p->dir;
}

void Player_Bullet_Update(Player *pp, Map *mp)
{ // 총알을 움직인다.
	int nowMap;
	int i;
	int j;

	for (i = 0; i < MAP_NUM; i++)
	{
		if (mp[i].onoff == 1)
		{
			nowMap = i;
			break;
		}
	}

	for (i = 0; i < 5; i++) // bullet 배열의 모든 요소들을 다 본다.
	{
		if( pp->bullet[i].range > 0 ) // range가 남아 있으면 총알을 그린다.
		{
			if ((pp->bullet[i].x != pp->x) || (pp->bullet[i].y != pp->y))
			{
				gotoxy(pp->bullet[i].x,pp->bullet[i].y);
				printf("  ");
			}
			pp->bullet[i].range--;
			switch(pp->bullet[i].dir)
			{
			case 0:
				pp->bullet[i].y--;
				break;
			case 1:
				pp->bullet[i].y++;
				break;
			case 2:
				pp->bullet[i].x-=2;
				break;
			case 3:
				pp->bullet[i].x+=2;
				break;
			}

			if (mp[nowMap].pMap[pp->bullet[i].y][pp->bullet[i].x / 2] != 0)
			{
				pp->bullet[i].range = 0;
				return;
				//break;
			}
			for (i = 0, j = 0; i < FLAG_NUM || j < PLAYER_BULLET_NUM; i++, j++)
			{
				if (j >= PLAYER_BULLET_NUM) j--;
				if (mp[nowMap].arFlag[i].x == pp->bullet[j].x && mp[nowMap].arFlag[i].y == pp->bullet[j].y)
				{
					return;
				}
			}

			gotoxy(pp->bullet[i].x, pp->bullet[i].y);

			if ((pp->bullet[i].x != pp->x) || (pp->bullet[i].y != pp->y))
			if (pp->bullet[i].range <= 0)
			{
				printf(" ");
			}
			else
			{
				printf("⊙");
			}
		}
	}
}