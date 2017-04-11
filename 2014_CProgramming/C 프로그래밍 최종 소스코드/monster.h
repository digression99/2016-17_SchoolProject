#pragma warning(disable:4996)
#pragma once

typedef struct _flag Flag;
typedef struct _monster Monster;

int compare(Player *pp, Map *mp, BOOL *key);
int calcDif(int pnum, int mnum, int xy);
void small_m_movement(Map *mp, int monNum, int key);
void monster_position(Player *pp, Map *mp);
int Distance (int const, int const, Monster *);
void toward(Player *pp, Map *mp, int monNum);
int cursor_case (int x);