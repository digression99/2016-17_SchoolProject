#include "MainTetris.h"

GameInfo::GameInfo()
:score(0), level(0), lines(0), stickRate(0), speed(0), mapColor(DARKGRAY), combo(0)
{}
void GameInfo::defaultSetting(int stage){

   //stage 1~10 ют╥б
   this->lines = 20 + (stage + stage) * (stage + stage) * 2 - 6 * stage * stage;//20*(stage);
   this->speed = 120 / (stage * stage);//1000 - 4 * (20 + 2 * stage * stage);
   this->level = stage;
   this->stickRate = 20-stage;
   this->mapColor = BLACK + stage;

}

void GameInfo::showSetting()
{
	gotoxy(MAP_LEFT + (MAP_WIDTH + 1) * 2, MAP_TOP + MAP_HEIGHT / 3);
	cout << "level ";
	gotoxy(MAP_LEFT + (MAP_WIDTH + 2) * 2, MAP_TOP + MAP_HEIGHT / 3 + 1);
	cout << this->level;
	gotoxy(MAP_LEFT + (MAP_WIDTH + 1) * 2, MAP_TOP + MAP_HEIGHT / 3 + 2);
	cout << "lines ";
	gotoxy(MAP_LEFT + (MAP_WIDTH + 2) * 2, MAP_TOP + MAP_HEIGHT / 3 + 3);
	cout << "  ";
	gotoxy(MAP_LEFT + (MAP_WIDTH + 2) * 2, MAP_TOP + MAP_HEIGHT / 3 + 3);
	cout << this->lines;
	gotoxy(MAP_LEFT + (MAP_WIDTH + 1) * 2, MAP_TOP + MAP_HEIGHT / 3 + 4);
	cout << "Score ";
	gotoxy(MAP_LEFT + (MAP_WIDTH + 2) * 2, MAP_TOP + MAP_HEIGHT / 3 + 5);
	cout << "  ";
	gotoxy(MAP_LEFT + (MAP_WIDTH + 2) * 2, MAP_TOP + MAP_HEIGHT / 3 + 5);
	cout << this->score;
}

void GameInfo::minusLine()
{
   this->lines--;
   this->score += (level*combo*10);
   this->combo++;
}