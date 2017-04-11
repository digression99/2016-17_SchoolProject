#include "Data.h"

void Player_Shoot(Player *p)
{ // �Ѿ��� �ʱ�ȭ�ϴ� �Ͱ� ����. Bullet_Init����.
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
{ // �Ѿ��� �����δ�.
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

	for (i = 0; i < 5; i++) // bullet �迭�� ��� ��ҵ��� �� ����.
	{
		if( pp->bullet[i].range > 0 ) // range�� ���� ������ �Ѿ��� �׸���.
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
				printf("��");
			}
		}
	}
}