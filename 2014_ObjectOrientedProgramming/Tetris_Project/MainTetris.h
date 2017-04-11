#pragma once
#pragma warning(disable:4996)

#include "Block.h"
#include "BlockPointer.h"
#include "GameInfo.h"
#include "MainData.h"
#include "PlayTetris.h"

#include <time.h>
#include <Windows.h>
#include <sys/timeb.h>
#include <ctime>
#include <conio.h>

#define COMMON_KEY 1 
#define SPECIAL_KEY 0 
#define F1 59 
#define F2 60 
#define F3 61 
#define F4 62 
#define F5 63 
#define F6 64 
#define F7 65 
#define F8 66 
#define F9 67 
#define F10 68 
#define UP_ARROW 72 
#define DOWN_ARROW 80 
#define LEFT_ARROW 75 
#define RIGHT_ARROW 77 
#define PAGEUP 73 
#define PAGEDOWN 81 
#define ENTER 13 
#define ESC 27 

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

#define D1 "¦®" 
#define D2 "¦±" 
#define D3 "¦¯" 
#define D4 "¦°" 
#define D9 "¦­" 
#define D10 "¦¬" 

void textColor(int foreground, int background);
int gotoxy(int x,int y);
void showMap(int select);
bool dealInput(int key, PlayTetris & pt);
bool getInput(PlayTetris & pt);
void setCursorView(char visible);
double diffclock(clock_t clock1,clock_t clock2);
char inKey(int *keyFlag);
void showMesBox(int x, int y, int w, int h);
void eraseMesBox(int x, int y, int w, int h);
void showMenu(int x, int y, char *str[], int size);
int menu(PlayTetris &pt);