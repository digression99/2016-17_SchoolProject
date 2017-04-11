#include "ALU.h"

int main(void)
{
	selectALU();
	return 0;
}

void addition(int* a, int* b, int* s)
{
	cout << "==========================덧셈========================" << endl;
	cout << "1. 이진수로 표현" << endl;
	cout << "피가수 : ";
	printBinary(a);
	cout << endl << "  가수 : ";
	printBinary(b);

	cout << endl << endl << "2. 덧셈 연산" << endl;
	cout << "  ";
	printBinary(a);
	cout << endl << "+ ";
	printBinary(b);
	cout << endl << "--------------------------------------------" << endl << "  ";
	adder_subtracter(PLUS, a, b, s);

	cout << "3. 10진수 결과값 : " << bin_to_dec(s) << endl << endl;
}
void subtraction(int* a, int* b, int* s)
{
	cout << "==========================뺄셈========================" << endl;
	cout << "1. 이진수로 표현" << endl;
	cout << "피감수 : ";
	printBinary(a);
	cout << endl << "  감수 : ";
	printBinary(b);

	cout << endl << endl << "2. 뺄셈 연산" << endl;
	cout << "  ";
	printBinary(a);
	cout << endl << "- ";
	printBinary(b);
	cout << endl << "--------------------------------------------" << endl << "  ";
	adder_subtracter(MINUS, a, b, s);

	cout << "3. 10진수 결과값 : " << bin_to_dec(s) << endl << endl;
}
void multiplication(int * bin1, int * bin2)
{
	cout << "==========================곱셈========================" << endl;

	int M[MAX_SIZE] = { 0, }, A[MAX_SIZE] = { 0, },
		Q[MAX_SIZE] = { 0, }, R[64] = { 0, }; // R:A+Q
	int i;
	int q1 = 0, q31 = 0;	// q1 : 1-비트 레지스터

	

	for (i = 0; i < MAX_SIZE; i++)
	{
		Q[i] = bin2[i];
		M[i] = bin1[i];
	}
	cout << "#초기값" << endl;
	cout << "                    A                                           Q                      Q-1                     M                    " << endl;
	cout << "  ";
	printBinary(A);
	cout << " ｜ ";
	printBinary(Q);
	cout << " ｜ " << q1 << " ｜ ";
	printBinary(M);
	cout << endl;

	for (i = 0; i < MAX_SIZE; i++)
	{
		cout << "#" << i + 1 << endl;
		if (q1 == 0)
		{
			if (Q[0] == 1)
			{
				// 뺄셈
				adder_subtracter(MINUS, A, M, A, true);
				cout << " A←A-M" << endl;
				cout << "  ";
				printBinary(A);
				cout << " ｜ ";
				cout << endl;
			}
		}
		else if (q1 == 1)
		{
			if (Q[0] == 0)
			{
				// 덧셈
				adder_subtracter(PLUS, A, M, A, true);
				cout << " A←A+M" << endl;
				cout << "  ";
				printBinary(A);
				cout << " ｜ ";
				cout << endl;
			}
		}

		// RIGHT 쉬프트.
		q31 = A[0];
		q1 = Q[0];
		shift(A, RIGHT, !INIT);
		shift(Q, RIGHT, !INIT);
		Q[MAX_SIZE - 1] = q31;
		cout << " SHIFT" << endl;
		cout << "  ";
		printBinary(A);
		cout << " ｜ ";
		printBinary(Q);
		cout << " ｜ " << q1 << " ｜ ";
		printBinary(M);
		cout << endl;
	}
	for (int i = 0; i < MAX_SIZE; i++)
	{
		R[i] = Q[i];
		R[MAX_SIZE + i] = A[i];
	}
	cout << endl << "이진수 결과 값 : ";
	for (int i = MAX_SIZE*2; i > 0; i--)
	{
		if (i % 4 == 0 && i != MAX_SIZE64)
		{
			cout << " ";
		}
		cout << R[i - 1];
	}
	cout << endl << "10진수 결과 값 : " << bin_to_dec(R, 64) << endl << endl;
}
void division(int* bin1, int* bin2)
{
	cout << "=========================나눗셈=======================" << endl;

	bool flag = true;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (bin2[i])
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		cout << "0으로 나눌 수 없습니다" << endl;
		return;
	}

	int M[MAX_SIZE] = { 0, }, A[MAX_SIZE] = { 0, },
		Q[MAX_SIZE] = { 0, }, temp[MAX_SIZE] = { 0, };
	int i, j;
	int q1 = 0, q31 = 0;	// Q의 1-비트레지스터와 최상위비트
	int sign = 0;	// a의 부호를 저장하는 변수
	int check = 0;	// 제수와 피제수의 부호 체크

	for (i = 0; i < MAX_SIZE; i++)
	{
		Q[i] = bin1[i];
		M[i] = bin2[i];
	}
	if (Q[MAX_SIZE-1]==MINUS)	// 피제수가 음수이면 A는 1로 초기화
	{
		for (i = 0; i < MAX_SIZE; i++)
		{
			A[i] = 1;
		}
	}
	check = Q[MAX_SIZE - 1] ^ M[MAX_SIZE - 1]; // 제수와 피제수의 부호가 다르면 check는 1
	cout << "#초기값" << endl;
	cout << "                    A                                           Q                                           M                    " << endl;
	cout << "  ";
	printBinary(A);
	cout << " ｜ ";
	printBinary(Q);
	cout << " ｜ ";
	printBinary(M);
	cout << endl;

	for (int i = 0; i < MAX_SIZE; i++)
	{
		cout << "#" << i + 1 << endl;

		// 좌측 쉬프트
		q31 = Q[MAX_SIZE - 1];
		shift(A, LEFT, !INIT);
		shift(Q, LEFT, !INIT);
		sign = A[MAX_SIZE - 1];
		A[0] = q31;
		cout << " SHIFT" << endl;
		cout << "  ";
		printBinary(A);
		cout << " ｜ ";
		printBinary(Q);
		cout << " ｜ ";
		cout << endl;

		for (j = 0; j < MAX_SIZE; j++)
		{
			temp[j] = A[j]; // A 복원용
		}
		
		// A와 M의 부호가 같으면 뺄셈, 다르면 덧셈
		if (sign == M[MAX_SIZE - 1])
		{
			// 뺄셈
			adder_subtracter(MINUS, A, M, A, true);
			cout << " A←A-M" << endl;
			cout << "  ";
			printBinary(A);
			cout << " ｜ ";
			cout << endl;
		}
		else
		{	// 덧셈
			adder_subtracter(PLUS, A, M, A, true);
			cout << " A←A+M" << endl;
			cout << "  ";
			printBinary(A);
			cout << " ｜ ";
			cout << endl;
		}
		
		// 연산 전후 A의 부호가 같으면 성공, 다르면 실패
		if (sign == A[MAX_SIZE-1] || bin_to_dec(A)==0)	// 성공 or A == 0
		{
			Q[0] = 1;	// Q0을 1로 세트
			cout << " Q0 = 1" << endl;
		}
		else if (sign != A[MAX_SIZE - 1])	// 실패
		{
			cout << " 복원" << endl;
			for (j = 0; j < MAX_SIZE; j++)
			{
				A[j] = temp[j];	// 복원
			}
		}
		cout << "  ";
		printBinary(A);
		cout << " ｜ ";
		printBinary(Q);
		cout << " ｜ ";
		printBinary(M);
		cout << endl;
	}
	if (check) // 제수부호와 피제수부호가 다름
	{
		twosComplement(Q);	// 결과값의 보수가 몫
	}
	cout << endl << "이진수 몫 : ";
	printBinary(Q);
	cout << endl << "10진수 몫 : " << bin_to_dec(Q) << endl;
	cout << "이진수 나머지 : ";
	printBinary(A);
	cout << endl << "10진수 나머지 : " << bin_to_dec(A) << endl << endl;
}

void selectALU()
{
	int n;
	char select;
	while (1) {
		while (1)
		{
			cout << "연산의 종류를 선택하세요(1: 정수, 2: 실수) : ";
			cin >> n;
			if (cin.fail() || (n != 1 && n != 2))
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "다시 입력하세요 (최대:2147483647, 최소:-2147483648)" << endl;
				continue;
			}
			else
				break;
		}
		switch (n)
		{
		case 1:
			intALU();
			break;
		case 2:
			floatALU();
			break;
		default:
			break;
		}
		cout << endl << "계속하려면 아무키나 입력하세요(종료: q)" << endl;
		select = getch();
		if (select == 'q')
			break;
		else
			system("cls");
	}
}
void intALU()
{
	int n, m;	// 연산을 위한 정수
	int a[MAX_SIZE] = { 0, };	// n을 이진수로 바꾼 값 저장
	int b[MAX_SIZE] = { 0, };	// m을 이진수로 바꾼 값 저장
	int s[MAX_SIZE] = { 0, }; // 연산 결과를 저장하는 배열

	// 10진수 정수 2개 입력 받음
	intInput(n, m);

	// 10진수를 2진수로 표현
	dec_to_bin(n, a);
	dec_to_bin(m, b);

	addition(a, b, s);
	subtraction(a, b, s);
	multiplication(a, b);
	division(a, b);
}
void floatALU()
{
	double n, m;	// 연산을 위한 실수
	int a[MAX_SIZE] = { 0, };
	int b[MAX_SIZE] = { 0, };
	int c[MAX_SIZE] = { 0, };	// 연산 결과를 저장하는 배열

	// 10진수 실수 2개 입력 받음
	floatInput(n, m);


	// 10진수를 IEEE754표준으로 표현
	ieee(n, a);
	ieee(m, b);

	faddition(a, b, c);
	fbin_to_dec(c);
	fsubtraction(a, b, c);
	fbin_to_dec(c);
	fmultiplication(a, b, c);
	fbin_to_dec(c);
	if (m == 0)
	{
		cout << "0으로 나눌 수 없습니다" << endl;
		return;
	}
	fdivision(a, b, c);
	fbin_to_dec(c);
}
void intInput(int& n, int& m)
{
	while (1) {
		cout << "ㄴ 2개의 정수 입력 : ";
		cin >> n >> m;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "다시 입력하세요 (최대:2147483647, 최소:-2147483648)" << endl;
			continue;
		}
		else
			break;
	}
}
void floatInput(double& n, double& m)
{
	while (1) {
		cout << "ㄴ 2개의 실수 입력 : ";
		cin >> n >> m;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "다시 입력하세요 (최대:2147483647, 최소:-2147483648)" << endl;
			continue;
		}
		else
			break;
	}
}


void twosComplement(int* n, int bit)
{
	// 1의 보수
	for (int i = 0; i < bit; i++)
	{
		n[i] = 1 ^ n[i];
	}
	// 2의 보수
	n[0] += 1;
	for (int i = 0; i < bit - 1; i++)
	{
		if (n[i] == 2)
		{
			n[i + 1] += 1;
			n[i] = 0;
		}
		else
			break;
	}
	if (n[bit - 1] == 2)
	{
		n[bit - 1] = 0;
	}
}
void dec_to_bin(int dec, int* bin, int bit)
{
	if (dec == INT_MIN)
	{
		bin[bit - 1] = 1;
		return;
	}

	// 부호 체크
	bool flag = true;
	if (dec < 0)
	{
		flag = false;
		dec = -dec;
	}

	for (int i = 0; dec > 0; i++)
	{
		bin[i] = dec % 2;
		dec /= 2;
	}

	// 음수인 경우 2의 보수로 표현
	if (!flag)
		twosComplement(bin, bit);
}
int bin_to_dec(int* bin, int bit)
{	// 배열 원본 변경X
	int* bin2 = new int[bit];
	for (int i = 0; i < bit; i++)
	{
		bin2[i] = bin[i];
	}

	int dec = 0;
	bool flag = true;
	if (bin2[bit - 1]) // 음수인 경우 2의보수 취해줌
	{
		twosComplement(bin2, bit);
		flag = false;
	}
	for (int i = 0; i < bit; i++)
	{
		dec += bin2[i] * pow(2, i);
	}

	delete[] bin2;

	if (!flag)
	{
		return -dec;
	}
	else return dec;
}
void adder_subtracter(int sign, int* bin1, int* bin2, int* bin3, bool print, int bit)
{
	int c, s, z, v;
	c = sign;
	//int a[MAX_SIZE] = { 0 };
	//int b[MAX_SIZE] = { 0 };
	int* a = new int[bit];
	int* b = new int[bit];
	for (int i = 0; i < bit; i++)
	{
		a[i] = bin1[i];
		b[i] = bin2[i];
	}

	for (int i = 0; i < bit; i++)
	{
		b[i] = sign ^ b[i];

		bin3[i] = a[i] ^ b[i] ^ c;
		c = (a[i] ^ b[i])*c + a[i] * b[i];
		if (i == bit - 2)
		{
			v = c; // 내부캐리 저장
		}
	}

	// 플래그 값
	s = bin3[bit - 1];
	v = v ^ c; // 오버플로우, v플래그는 내부캐리와 외부캐리의 XOR
	z = 1;
	for (int i = 0; i < bit; i++)
	{
		if (bin3[i]) {	// NOR연산, 배열의 모든값이 0이면 z플래그는 1
			z = 0;
			break;
		}
	}

	if (!print)
	{
		printBinary(bin3);
		cout << endl << endl << "C : " << c << ", S : " << s << ", Z : " << z << ", V : " << v << endl << endl;
	}

	delete[] a;
	delete[] b;
}
void printBinary(int * bin, int bit)
{
	for (int i = bit; i > 0; i--)
	{
		if (i % 4 == 0 && i != bit) // 28일때, 0일때
		{
			cout << " ";
		}
		cout << bin[i - 1];
	}
}
int shift(int * bin, int flag, int flag2, int bit)
{ // flag1 : RIGHT OR LEFT flag2 : INIT OR NOT
	int t = 0;
	if (flag == LEFT)
	{ // flag가 1이면 left
		t = bin[bit - 1];
		for (int i = MAX_SIZE - 1; i > 0; i--)
		{
			bin[i] = bin[i - 1];
		}
		bin[0] = 0;
	}
	else
	{ // flag가 0이면 right
		int j = bin[bit - 1];
		t = bin[0];
		for (int i = 0; i < bit - 1; i++)
		{
			bin[i] = bin[i + 1];
		}
		if (!(flag2 == INIT))
			bin[bit - 1] = j;
		else
		{
			bin[bit - 1] = 0;
		}
	}
	// return -> 왼쪽 쉬프트 시 가장 왼쪽 비트[31]를,
	// 오른쪽 쉬프트 시 가장 오른쪽 비트[0]를 리턴
	return t;
}