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

void selectALU();		// ���� ���� �Լ�
void intALU();		// ���� ���� �Լ�
void floatALU();	// �Ǽ� ���� �Լ�
void intInput(int& n, int& m);			// ���� �Է� �Լ�
void floatInput(double& n, double& m);	// �Ǽ� �Է� �Լ�
void printBinary(int * bin, int bit = MAX_SIZE); // ������ ��� �Լ�
void arrPrint(int* a, int n);

void twosComplement(int* n, int bit = MAX_SIZE);	// 2�� ������ ǥ���ϴ� �Լ�
void dec_to_bin(int dec, int* bin, int bit = MAX_SIZE);	// 10������ 2������ ����� �Լ�
int bin_to_dec(int* bin, int bit = MAX_SIZE); // 2������ 10������ ����� �Լ�
void adder_subtracter(int sign, int* bin1, int* bin2, int* bin3, bool print = false, int bit = MAX_SIZE);	// ���İ������
																						// sign 0:����, 1:����
																						// print true:�÷������X (����, ������ ��)
int shift(int * bin, int flag, int flag2, int bit = MAX_SIZE);

// ����
void addition(int* a, int* b, int* s);
void subtraction(int* a, int* b, int* s);
void multiplication(int* bin1, int* bin2);
void division(int* bin1, int* bin2);
// �Ǽ�
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