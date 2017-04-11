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
	//int tetrisMap[MAP_HEIGHT][MAP_WIDTH];	// 테트리스 바탕 맵
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
	//void setTetrisMap();			// tetrisMap 배열 생성, 
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

	void genDefaultBlock();	// default block 생성
	Block getRandBlock();		//랜덤으로 블록 기본 모형 리턴
	void setNextBlock();	//생성된 랜덤 블록 객체 nextBlock 에 저장
	
	//void moveBlock(BlockPointer& cp);// 블록의 cp의 y값을 하나 내린다.
	void eraseBlock();	//블록 지움
	void showBlock();	//블록 보여줌

	void shiftBlock();	//블록을 shift 시킴
	void unShiftBlock();
	void showTetrisMap(int select);

	void startBlock();

	//void showTetrisMap(); // 현재 맵 상황을 보여줌
	void showNextBlock();	// 다음 블록을 보여줌
	void showShiftBlock(); // shift된 블록을 보여줌
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
	bool checkBlock();	//블록이 닿아는지 체크  닿으면 true 안닿으면 false
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

	//블록 객체 만들고 cp 를 받아서 도형을 보여줌
	//사용자가 키보드를 입력 안하면 블록이 걸리는지 checking - > move 
};