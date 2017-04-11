#include "Data.h"

void gotoxy(int x, int y)
{
	COORD pos = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void removeCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void displayCursor(void) 
 { 
 // 커서를 살리는 코드 부분 
CONSOLE_CURSOR_INFO ConCurInf; 
 ConCurInf.dwSize = 10; 
 ConCurInf.bVisible = TRUE; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&ConCurInf); 
 } 