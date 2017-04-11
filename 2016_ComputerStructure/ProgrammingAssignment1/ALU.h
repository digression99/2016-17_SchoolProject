#pragma warning(disable:4996)

#include <iostream>
#include <cmath>
#include <climits>
#include <stdlib.h>
#include <conio.h>

#define MAX_SIZE 32
#define MAX_SIZE64 64

#define LEFT 1
#define RIGHT 0
#define INIT 0
#define PLUS 0
#define MINUS 1

#define MF 8
#define EF 23
#define MF_S 1
#define EF_S 9

using namespace std;

void selectALU();		// 연산 선택 함수
void intALU();		// 정수 연산 함수
void floatALU();	// 실수 연산 함수
void intInput(int& n, int& m);			// 정수 입력 함수
void floatInput(double& n, double& m);	// 실수 입력 함수
void printBinary(int * bin, int bit = MAX_SIZE); // 이진수 출력 함수
void arrPrint(int* a, int n);

void twosComplement(int* n, int bit = MAX_SIZE);	// 2의 보수로 표현하는 함수
void dec_to_bin(int dec, int* bin, int bit = MAX_SIZE);	// 10진수를 2진수로 만드는 함수
int bin_to_dec(int* bin, int bit = MAX_SIZE); // 2진수를 10진수로 만드는 함수
void adder_subtracter(int sign, int* bin1, int* bin2, int* bin3, bool print = false, int bit = MAX_SIZE);	// 병렬가감산기
																						// sign 0:덧셈, 1:뺄셈
																						// print true:플래그출력X (곱셈, 나눗셈 용)
int shift(int * bin, int flag, int flag2, int bit = MAX_SIZE);

// 정수
void addition(int* a, int* b, int* s);
void subtraction(int* a, int* b, int* s);
void multiplication(int* bin1, int* bin2);
void division(int* bin1, int* bin2);
// 실수
void ieee(double a, int *arr);
void fdec_to_bin1(double num, int* bin);
void fdec_to_bin2(double num, int* bin);
void fbin_to_dec(int* ieee);
int bin_to_dec2(int* bin, int bit);
void faddition(int* a, int* b, int* c);
void fsubtraction(int* a, int* b, int* c);
void fmultiplication(int * a, int * b, int * c);
void multiplication2(int * bin1, int * bin2, int * bin3, int size);
void fdivision(int* a, int* b, int* c);
void division2(int* bin1, int* bin2, int size);