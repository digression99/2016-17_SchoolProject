#pragma once

#include<iostream>
#include <time.h>
#include "GameInfo.h"
#include "Block.h"

#define MAP_WIDTH 16
#define MAP_HEIGHT 21
#define STAGE_NUM 10
#define MAX_HEIGHT 24
#define MAX_WIDTH 80
#define MAP_LEFT (MAX_WIDTH / 8)
#define MAP_TOP (MAX_HEIGHT / 12)
#define MAP_NUM 10

#define BLOCK_VOID 0
#define BLOCK_WALL 1
#define BLOCK_ITEM1 2
#define BLOCK_ITEM2 3

#define KEY_SPEED 300

class PlayTetris{
private:
	//int tetrisMap[MAP_HEIGHT][MAP_WIDTH];	// ��Ʈ���� ���� ��
	BlockPointer mergeMap[MAP_HEIGHT][MAP_WIDTH];
	BlockPointer itemArr[MAP_WIDTH]; // corrected
	int itemArrIdx;
	GameInfo g;
	Block bArr[7];
	Block movingBlock;
	Block shiftedBlock;
	Block nextBlock;
	Block nextNextBlock;
	//BlockPointer movbp;
	bool isOver;
	bool isMerged;
	bool keyFree;
	bool isShifted;
	bool isFirst;
	//bool isReal;

	//char chTetrisMap[MAP_HEIGHT][MAP_WIDTH + 1];
	unsigned short bitMap[MAP_HEIGHT];
	//int oneStack[MAP_HEIGHT - 1];
public:
	PlayTetris();
	//void setTetrisMap();			// tetrisMap �迭 ����, 
	/*void setMovbp(int x, int y);
	BlockPointer * getMovbp() 
	{
		return &this->movbp;
	}*/

	Block * getMovingBlock()
	{
		return &this->movingBlock;
	}

	GameInfo * getGameInfo()
	{
		return &this->g;
	}

	bool getIsOver() { return this->isOver; }
	void setIsOver(bool b) { this->isOver = b; }

	void genDefaultBlock();	// default block ����
	Block getRandBlock();		//�������� ��� �⺻ ���� ����
	void setNextBlock();	//������ ���� ��� ��ü nextBlock �� ����
	
	//void moveBlock(BlockPointer& cp);// ����� cp�� y���� �ϳ� ������.
	void eraseBlock();	//��� ����
	void showBlock();	//��� ������

	void shiftBlock();	//����� shift ��Ŵ
	void unShiftBlock();
	void showTetrisMap(int select);

	void startBlock();

	//void showTetrisMap(); // ���� �� ��Ȳ�� ������
	void showNextBlock();	// ���� ����� ������
	void showShiftBlock(); // shift�� ����� ������
	void showMovingBlock();

	//void makeIntMap();
	//void makeCharMap();
	void makeBitMap();
	void makeOneStack();
	//void printCharMap();
	void printBitMap();
	//void printOneStack();
	//void printIntMap();
	//void setMap(int num);

	bool checkLine();
	bool mergeBlock();
	bool checkBlock();	//����� ��ƴ��� üũ  ������ true �ȴ����� false
	bool checkWall();

	bool checkLeftWall();
	bool checkRightWall();

	void deleteLine(int y);
	void downBlock();

	void setIsMerged(bool b) {this->isMerged = b;}
	bool getIsMerged() { return this->isMerged; }
	//void resetMovbp();

	void makeMergeMap();
	//bool makeMergeMap();
	void showMergeMap();

	void setKeyFree(bool b) { this->keyFree = b; }
	bool getKeyFree() { return this->keyFree; }

	bool rotationCheck();
	void swapBlock(Block * b1, Block * b2);

	bool getIsShifted() { return this->isShifted; }
	bool setIsShifted(bool b) { this->isShifted = b; }

	int getItemArrIdx() { return this->itemArrIdx; }
	void setItemArrIdx(int idx) { this->itemArrIdx = idx; }

	void itemEffect(int x, int y, int data);

	void deletePixel();
	void compressPixel();

	void setMergeMap(int mn);

	void rotateBlock();
	void leftBlock();
	void rightBlock();

	bool getIsFirst() { return this->isFirst; }
	void setIsFirst(bool b) { this->isFirst = b; }
	//void setTetrisMap();

	//��� ��ü ����� cp �� �޾Ƽ� ������ ������
	//����ڰ� Ű���带 �Է� ���ϸ� ����� �ɸ����� checking - > move 
};