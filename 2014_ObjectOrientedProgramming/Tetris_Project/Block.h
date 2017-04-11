#pragma once

#include <iostream>
using namespace std;
#include "BlockPointer.h"
#include <windows.h>


class Block
{
private:
	BlockPointer bp[3];
	BlockPointer absp;
	// absolute position
	int color;
public:
	int ar[5][5];
	Block();
	Block(BlockPointer & bp1, BlockPointer & bp2, BlockPointer & bp3,
		BlockPointer & absp,
		int color);
	~Block();
	Block(const Block & b);
	Block &operator=(const Block & b);
	void constructAr();
	void printArr(); // for debugging
	void rotate();
	BlockPointer * getAbsp() { return &this->absp; }
	void setAbsp(int x, int y) {
		this->absp.setX(x);
		this->absp.setY(y);
	}
	BlockPointer * getBp()
	{
		return this->bp;
	}
	int getColor() { return this->color; }
	void setColor(int c) { this->color = c; }
	void erase();
	void print();
};