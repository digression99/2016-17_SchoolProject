#pragma once
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <conio.h>
#include <windows.h>
#include <assert.h>

#define WINNUM 3
#define GAMENUM 5
// GAMENUM, WINNUM은 무조건 홀수여야.


void Interface(char ***arfp);
void gotoxy(int x, int y);
void Destroy(char **arfp);
BOOL Game(int *count);
void clear(int x, int y, int mx, int my);
void displayCursor(void);
void removeCursor(void);
BOOL Rcp();