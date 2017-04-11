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
   GameInfo(); // ����ڿ��� ���������� �Է¹޾Ƽ� level �� ���� defaultsetting�� ���������Ͽ� setting
   void defaultSetting(int Stage);//����ڿ��� �Է¹��� ���������� �������� default setting�� �Ѵ�.
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