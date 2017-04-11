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

#define MAX_X 50 // x의 최대 위치
#define MAX_Y 20 // y의 최대 위치
#define FLAG_NUM 10 // 플래그 개수
#define MONSTER_BETWEEN 30 // 몬스터와 캐릭터 사이의 거리
#define MONSTER_NUM 5 // 몬스터 최대 마리 수
#define MAP_NUM 3
#define MONSTER_BULLET_NUM 3 //몬스터의 총알 개수
#define PLAYER_BULLET_NUM 5 // 캐릭터의 총알 개수
#define M_HP 100 //몬스터의 체력
#define CHARACTER_FIGURE "●"
#define MONSTER_FIGURE "▲"
#define FLAG_FIGURE "◁"
#define GATE_FIGURE "＠"
#define WALL_FIGURE "▨"
#define D1 "┏" 
#define D2 "┗" 
#define D3 "┓" 
#define D4 "┛" 
#define D9 "┃" 
#define D10 "━" 

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ENTER 13
#define ESC 27

#define INITX 2;// 캐릭터의 시작 위치
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
	int dir; // 최근에 움직인 플레이어의 방향을 저장한다.
	int shootdelay;
	Bullet bullet[5];
	int bNum; // 현재 출력되어 있는 총알의 개수를 저장한다.
	BOOL display;
	BOOL MapChanged;
} Player;

typedef struct _monster
{
	int x;
	int y;
	BOOL monster_enable; // 1이면 나와서 움직임. 0이면 출력이 안됨.
	int hp; // 몬스터의 체력.
	int xybullet[MONSTER_BULLET_NUM][2];
	BOOL display;
	int delay;
	BOOL isMoved; // isMoved가 1이면 몬스터를 지우고 0이 된다.
} Monster;

typedef struct _flag
{ // 캐릭터 위치와 플래그 위치가 같으면 flag_enable이 0에서 1이 됨.
	int x; // 그러면 몬스터 display가 0에서 1이 됨.
	int y;
	BOOL flag_enable; // 깃발을 열고 깃발이 사라짐.
	BOOL display; 
} Flag;

typedef struct _map
{ // 남아 있는 몬스터의 마리 수, flag의 개수는 어떻게 정할 것인가.
	int pMap[100][100]; // 깃발 : flag_enable로 열고 닫고를 정할 수 있다.
	char cMap[300][300];
	int mapnum;         // 몬스터 : monster_enable과 hp로 할 수 있다.
	int width, height; // mapnum 필요없을듯.
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