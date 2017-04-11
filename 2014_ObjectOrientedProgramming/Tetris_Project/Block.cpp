#include "MainTetris.h"

Block::Block() 
: color(BLACK)
{
	for (int i = 0; i < 3; i++)
	{
		this->bp[i].setX(0);
		this->bp[i].setY(0);
		this->bp[i].setColor(BLACK);
		this->bp[i].setData(BLOCK_VOID);
	}
	this->absp.setX(0);
	this->absp.setY(0);
	this->absp.setColor(BLACK);
	this->absp.setData(BLOCK_VOID);
	constructAr();
}

Block::Block(BlockPointer & bp1, BlockPointer & bp2, 
	BlockPointer & bp3, BlockPointer & absp, int color)
{
	this->bp[0] = bp1;
	this->bp[1] = bp2;
	this->bp[2] = bp3;
	this->color = color;
	this->absp = absp;
	constructAr();
}

Block::~Block()
{}

Block::Block(const Block & b) : color(b.color)
{
	for (int i = 0; i < 3; i++)
	{
		this->bp[i] = b.bp[i];
	}
	this->absp = b.absp;
	constructAr();
}

Block &Block::operator=(const Block & b)
{
	this->color = b.color;
	for (int i = 0; i < 3; i++)
	{
		this->bp[i] = b.bp[i];
	}
	this->absp = b.absp;
	constructAr();
	return *this;
}

void Block::constructAr()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			ar[i][j] = 0;
			if (i == 2 && j == 2)
			{
				ar[i][j] = 1;
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		ar[this->bp[i].getY()][this->bp[i].getX()] = 1;
	}
}

void Block::printArr()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << this->ar[i][j] << " ";
		}
		cout << endl;
	}
}

void Block::rotate()
{
	for (int i = 0; i < 3; i++)
	{
		int tempX = this->bp[i].getX();
		int tempY = this->bp[i].getY();
		this->bp[i].setX(tempX - 2);
		this->bp[i].setY(tempY - 2);

		int temp = this->bp[i].getX();
		this->bp[i].setX(-this->bp[i].getY());
		this->bp[i].setY(temp);

		tempX = this->bp[i].getX();
		tempY = this->bp[i].getY();

		this->bp[i].setX(tempX + 2);
		this->bp[i].setY(tempY + 2);
	}
	constructAr();
}

void Block::print()
{
   int x = this->absp.getX() + 4; // center ÀÇ Àý´ë x ÁÂÇ¥
   int y = this->absp.getY() + 2; // center ÀÇ Àý´ë y ÁÂÇ¥

   textColor(this->color, BLACK);
   gotoxy(x, y);
   cout << "¡á";

   for (int i = 0; i < 3; i++)
   {
      gotoxy(x + 2 * (this->getBp()[i].getX() - 2), y + this->getBp()[i].getY() - 2);
      textColor(this->getBp()[i].getColor(),BLACK);
      cout << "¡á";
   }
   textColor(DARKGRAY, BLACK);
}

void Block::erase()
{
	int x = this->absp.getX() + 4; // center ÀÇ Àý´ë x ÁÂÇ¥
	int y = this->absp.getY() + 2; // center ÀÇ Àý´ë y ÁÂÇ¥

	gotoxy(x, y);
	cout << "  ";

	for (int i = 0; i < 3; i++)
	{
		gotoxy(x + 2 * (this->getBp()[i].getX() - 2), y + this->getBp()[i].getY() - 2);
		cout << "  ";
	}
}