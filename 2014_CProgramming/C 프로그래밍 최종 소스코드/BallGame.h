#pragma once

//////////////////////////////
// BallGame의 상수들
#define MAX_LEFT 0
#define MAX_UP 0
#define ROW_SIZE 100
#define COL_SIZE 40
#define NUMSIZE 4
#define BACKSPACE 8
#define BALLGAME_ENDNUM 11
/////////////////////////////

void Setting(char **gnp, char **ipnp);
void Interface(char ***arfp);
void InputNum(char **gnp, char **ipnp, int *count, int *result);
void Destroy(char **gnp, char **ipnp, char ***arfp);
void NumCheck(char **gnp, char **ipnp, int *rp);
BOOL Result(char *gnp, int *result, int *count, BOOL *WinLose);
BOOL BallGame();