#include "MainTetris.h"

BlockPointer::BlockPointer() : x(0), y(0), color(BLACK), data(BLOCK_VOID)
{}

BlockPointer::BlockPointer(int x, int y, int color, int data) : x(x), y(y), color(color), data(data)
{}

BlockPointer::BlockPointer(const BlockPointer &b) : x(b.x), y(b.y), color(b.color), data(b.data)
{}

BlockPointer::~BlockPointer()
{}

BlockPointer & BlockPointer::operator=(BlockPointer &b)
{
	this->x = b.x;
	this->y = b.y;
	this->color = b.color;
	this->data = b.data;
	return *this;
}

BlockPointer & BlockPointer::operator=(const BlockPointer &b)
{
	this->x = b.x;
	this->y = b.y;
	this->color = b.color;
	this->data = b.data;
	return *this;
}

void BlockPointer::setColor(int color){

	this->color = color;
}
void BlockPointer::setX(int x)
{
	this->x = x;
}

int BlockPointer::getX()
{
	return this->x;
}

void BlockPointer::setY(int y)
{
	this->y = y;
}

int BlockPointer::getColor(){
	return this->color;
}
int BlockPointer::getY()
{
	return this->y;
}