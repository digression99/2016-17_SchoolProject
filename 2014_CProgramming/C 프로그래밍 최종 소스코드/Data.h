#pragma once

#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <malloc.h>
#include <assert.h>
/////////////////////////////////////////
#include "map.h"
#include "monster.h"
#include "player.h"
#include "systemFunc.h"
#include "BallGame.h"
#include "Rcp.h"

#define MAX_X 50 // x�� �ִ� ��ġ
#define MAX_Y 20 // y�� �ִ� ��ġ
#define FLAG_NUM 10 // �÷��� ����
#define MONSTER_BETWEEN 30 // ���Ϳ� ĳ���� ������ �Ÿ�
#define MONSTER_NUM 5 // ���� �ִ� ���� ��
#define MAP_NUM 3
#define MONSTER_BULLET_NUM 3 //������ �Ѿ� ����
#define PLAYER_BULLET_NUM 5 // ĳ������ �Ѿ� ����
#define M_HP 100 //������ ü��
#define CHARACTER_FIGURE "��"
#define MONSTER_FIGURE "��"
#define FLAG_FIGURE "��"
#define GATE_FIGURE "��"
#define WALL_FIGURE "��"
#define D1 "��" 
#define D2 "��" 
#define D3 "��" 
#define D4 "��" 
#define D9 "��" 
#define D10 "��" 

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ENTER 13
#define ESC 27

#define INITX 2;// ĳ������ ���� ��ġ
#define INITY 1;

#define BOX_LEFT 30
#define BOX_UP 10
#define MES_LEFT (BOX_LEFT + 10)
#define MES_UP (BOX_UP + 5)

int map1[30][30];
int map2[15][30];
int map3[30][30];

typedef struct _bullet
{
	int x, y;
	int dir;
	int range;
} Bullet;

typedef struct _player
{
	int interval, bulletinterval;
	int health;
	int x, y;
	int money;
	int damage;
	int dir; // �ֱٿ� ������ �÷��̾��� ������ �����Ѵ�.
	int shootdelay;
	Bullet bullet[5];
	int bNum; // ���� ��µǾ� �ִ� �Ѿ��� ������ �����Ѵ�.
	BOOL display;
	BOOL MapChanged;
} Player;

typedef struct _monster
{
	int x;
	int y;
	BOOL monster_enable; // 1�̸� ���ͼ� ������. 0�̸� ����� �ȵ�.
	int hp; // ������ ü��.
	int xybullet[MONSTER_BULLET_NUM][2];
	BOOL display;
	int delay;
	BOOL isMoved; // isMoved�� 1�̸� ���͸� ����� 0�� �ȴ�.
} Monster;

typedef struct _flag
{ // ĳ���� ��ġ�� �÷��� ��ġ�� ������ flag_enable�� 0���� 1�� ��.
	int x; // �׷��� ���� display�� 0���� 1�� ��.
	int y;
	BOOL flag_enable; // ����� ���� ����� �����.
	BOOL display; 
} Flag;

typedef struct _map
{ // ���� �ִ� ������ ���� ��, flag�� ������ ��� ���� ���ΰ�.
	int pMap[100][100]; // ��� : flag_enable�� ���� �ݰ� ���� �� �ִ�.
	char cMap[300][300];
	int mapnum;         // ���� : monster_enable�� hp�� �� �� �ִ�.
	int width, height; // mapnum �ʿ������.
	//int flagnum;
	Flag arFlag[FLAG_NUM];
	Monster arMonster[MONSTER_NUM];
	BOOL onoff;
	BOOL display;
} Map;

void Init(Player *pp, Map *mp);
void Map_Init(Map *mp);
void Monster_Init(Map *mp);
void Flag_Init(Map *mp);
void Player_Init(Player *player);

void Player_Update(Player *pp, Map *mp, int *oldx, int *oldy);
void Player_Print(Player *pp, int *oldx, int *oldy);
void Player_Move(Player *pp, Map *mp);
void Player_Change(Player *pp, Map *mp);

void Monster_Update(Player *pp, Map *mp, int *monster_Frame, int *monster_FrameF);
void Monster_Print(Map *mp);
void Monster_Move(Player *pp, Map *mp, int *monster_Frame, int *monster_FrameF);
void Monster_Change(Player *pp, Map *mp);

void Map_SingleMapInit(Map *m, int stage);
void Map_Update(Player *pp, Map *mp);
void Map_Print(Map *mp);
void Map_Change(Player *pp, Map *mp);

void Flag_Update(Player *pp, Map *mp);
void Flag_Print(Map *mp);
void Flag_Change(Player *pp, Map *mp);

void DeleteMessage(char *str);
void DrawBigBox(int size, int num);
void PrintBox(char *str, int num);
int SelectSquare(char *str[], int num);
void DeleteBox(char *str, int num);
void ShowMessage(char *str);
void ShowMessage2(char *str);

void displayFalse(Player *pp, Map *mp);