#pragma once

#include <iostream>
using namespace std;

class BlockPointer
{
private:
	int x;
	int y;
	int color;
	int data;
public:
	BlockPointer();
	BlockPointer(int x, int y, int color, int data);
	BlockPointer(const BlockPointer &b);
	~BlockPointer();
	BlockPointer & operator=(BlockPointer &b);
	BlockPointer & operator=(const BlockPointer &b);
	void setColor(int color);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	int getColor();
	int getData() { return this->data; }
	void setData(int d) { this->data = d; }
};