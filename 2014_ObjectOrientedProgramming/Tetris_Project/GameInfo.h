#pragma once

#include<iostream>
class GameInfo{
private:
   int score;
   int speed;
   int level;
   int lines;
   int stickRate;
   int mapColor;
   int combo;
public:
   GameInfo(); // 사용자에게 스테이지를 입력받아서 level 에 저장 defaultsetting에 인자전달하여 setting
   void defaultSetting(int Stage);//사용자에게 입력받은 스테이지를 바탕으로 default setting을 한다.
   void showSetting();
   int getSpeed() { return this->speed; }
   int getMapColor() { return this->mapColor; }
   void setMapColor(int color) { this->mapColor = color; }

   void addScore(int bonus){
	   this->score += bonus;
   }
   void minusLine();
   void setCombo(int c) { this->combo = c; }
   int getCombo() { return this->combo; }
   void setLevel(int l) { this->level = l; }
   int getLines() { return this->lines; }
   int getLevel() { return this->level; }
};