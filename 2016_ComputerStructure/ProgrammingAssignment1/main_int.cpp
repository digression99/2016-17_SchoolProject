#include "ALU.h"

int main(void)
{
	selectALU();
	return 0;
}

void addition(int* a, int* b, int* s)
{
	cout << "==========================����========================" << endl;
	cout << "1. �������� ǥ��" << endl;
	cout << "�ǰ��� : ";
	printBinary(a);
	cout << endl << "  ���� : ";
	printBinary(b);

	cout << endl << endl << "2. ���� ����" << endl;
	cout << "  ";
	printBinary(a);
	cout << endl << "+ ";
	printBinary(b);
	cout << endl << "--------------------------------------------" << endl << "  ";
	adder_subtracter(PLUS, a, b, s);

	cout << "3. 10���� ����� : " << bin_to_dec(s) << endl << endl;
}
void subtraction(int* a, int* b, int* s)
{
	cout << "==========================����========================" << endl;
	cout << "1. �������� ǥ��" << endl;
	cout << "�ǰ��� : ";
	printBinary(a);
	cout << endl << "  ���� : ";
	printBinary(b);

	cout << endl << endl << "2. ���� ����" << endl;
	cout << "  ";
	printBinary(a);
	cout << endl << "- ";
	printBinary(b);
	cout << endl << "--------------------------------------------" << endl << "  ";
	adder_subtracter(MINUS, a, b, s);

	cout << "3. 10���� ����� : " << bin_to_dec(s) << endl << endl;
}
void multiplication(int * bin1, int * bin2)
{
	cout << "==========================����========================" << endl;

	int M[MAX_SIZE] = { 0, }, A[MAX_SIZE] = { 0, },
		Q[MAX_SIZE] = { 0, }, R[64] = { 0, }; // R:A+Q
	int i;
	int q1 = 0, q31 = 0;	// q1 : 1-��Ʈ ��������

	

	for (i = 0; i < MAX_SIZE; i++)
	{
		Q[i] = bin2[i];
		M[i] = bin1[i];
	}
	cout << "#�ʱⰪ" << endl;
	cout << "                    A                                           Q                      Q-1                     M                    " << endl;
	cout << "  ";
	printBinary(A);
	cout << " �� ";
	printBinary(Q);
	cout << " �� " << q1 << " �� ";
	printBinary(M);
	cout << endl;

	for (i = 0; i < MAX_SIZE; i++)
	{
		cout << "#" << i + 1 << endl;
		if (q1 == 0)
		{
			if (Q[0] == 1)
			{
				// ����
				adder_subtracter(MINUS, A, M, A, true);
				cout << " A��A-M" << endl;
				cout << "  ";
				printBinary(A);
				cout << " �� ";
				cout << endl;
			}
		}
		else if (q1 == 1)
		{
			if (Q[0] == 0)
			{
				// ����
				adder_subtracter(PLUS, A, M, A, true);
				cout << " A��A+M" << endl;
				cout << "  ";
				printBinary(A);
				cout << " �� ";
				cout << endl;
			}
		}

		// RIGHT ����Ʈ.
		q31 = A[0];
		q1 = Q[0];
		shift(A, RIGHT, !INIT);
		shift(Q, RIGHT, !INIT);
		Q[MAX_SIZE - 1] = q31;
		cout << " SHIFT" << endl;
		cout << "  ";
		printBinary(A);
		cout << " �� ";
		printBinary(Q);
		cout << " �� " << q1 << " �� ";
		printBinary(M);
		cout << endl;
	}
	for (int i = 0; i < MAX_SIZE; i++)
	{
		R[i] = Q[i];
		R[MAX_SIZE + i] = A[i];
	}
	cout << endl << "������ ��� �� : ";
	for (int i = MAX_SIZE*2; i > 0; i--)
	{
		if (i % 4 == 0 && i != MAX_SIZE64)
		{
			cout << " ";
		}
		cout << R[i - 1];
	}
	cout << endl << "10���� ��� �� : " << bin_to_dec(R, 64) << endl << endl;
}
void division(int* bin1, int* bin2)
{
	cout << "=========================������=======================" << endl;

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
		cout << "0���� ���� �� �����ϴ�" << endl;
		return;
	}

	int M[MAX_SIZE] = { 0, }, A[MAX_SIZE] = { 0, },
		Q[MAX_SIZE] = { 0, }, temp[MAX_SIZE] = { 0, };
	int i, j;
	int q1 = 0, q31 = 0;	// Q�� 1-��Ʈ�������Ϳ� �ֻ�����Ʈ
	int sign = 0;	// a�� ��ȣ�� �����ϴ� ����
	int check = 0;	// ������ �������� ��ȣ üũ

	for (i = 0; i < MAX_SIZE; i++)
	{
		Q[i] = bin1[i];
		M[i] = bin2[i];
	}
	if (Q[MAX_SIZE-1]==MINUS)	// �������� �����̸� A�� 1�� �ʱ�ȭ
	{
		for (i = 0; i < MAX_SIZE; i++)
		{
			A[i] = 1;
		}
	}
	check = Q[MAX_SIZE - 1] ^ M[MAX_SIZE - 1]; // ������ �������� ��ȣ�� �ٸ��� check�� 1
	cout << "#�ʱⰪ" << endl;
	cout << "                    A                                           Q                                           M                    " << endl;
	cout << "  ";
	printBinary(A);
	cout << " �� ";
	printBinary(Q);
	cout << " �� ";
	printBinary(M);
	cout << endl;

	for (int i = 0; i < MAX_SIZE; i++)
	{
		cout << "#" << i + 1 << endl;

		// ���� ����Ʈ
		q31 = Q[MAX_SIZE - 1];
		shift(A, LEFT, !INIT);
		shift(Q, LEFT, !INIT);
		sign = A[MAX_SIZE - 1];
		A[0] = q31;
		cout << " SHIFT" << endl;
		cout << "  ";
		printBinary(A);
		cout << " �� ";
		printBinary(Q);
		cout << " �� ";
		cout << endl;

		for (j = 0; j < MAX_SIZE; j++)
		{
			temp[j] = A[j]; // A ������
		}
		
		// A�� M�� ��ȣ�� ������ ����, �ٸ��� ����
		if (sign == M[MAX_SIZE - 1])
		{
			// ����
			adder_subtracter(MINUS, A, M, A, true);
			cout << " A��A-M" << endl;
			cout << "  ";
			printBinary(A);
			cout << " �� ";
			cout << endl;
		}
		else
		{	// ����
			adder_subtracter(PLUS, A, M, A, true);
			cout << " A��A+M" << endl;
			cout << "  ";
			printBinary(A);
			cout << " �� ";
			cout << endl;
		}
		
		// ���� ���� A�� ��ȣ�� ������ ����, �ٸ��� ����
		if (sign == A[MAX_SIZE-1] || bin_to_dec(A)==0)	// ���� or A == 0
		{
			Q[0] = 1;	// Q0�� 1�� ��Ʈ
			cout << " Q0 = 1" << endl;
		}
		else if (sign != A[MAX_SIZE - 1])	// ����
		{
			cout << " ����" << endl;
			for (j = 0; j < MAX_SIZE; j++)
			{
				A[j] = temp[j];	// ����
			}
		}
		cout << "  ";
		printBinary(A);
		cout << " �� ";
		printBinary(Q);
		cout << " �� ";
		printBinary(M);
		cout << endl;
	}
	if (check) // ������ȣ�� ��������ȣ�� �ٸ�
	{
		twosComplement(Q);	// ������� ������ ��
	}
	cout << endl << "������ �� : ";
	printBinary(Q);
	cout << endl << "10���� �� : " << bin_to_dec(Q) << endl;
	cout << "������ ������ : ";
	printBinary(A);
	cout << endl << "10���� ������ : " << bin_to_dec(A) << endl << endl;
}

void selectALU()
{
	int n;
	char select;
	while (1) {
		while (1)
		{
			cout << "������ ������ �����ϼ���(1: ����, 2: �Ǽ�) : ";
			cin >> n;
			if (cin.fail() || (n != 1 && n != 2))
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "�ٽ� �Է��ϼ��� (�ִ�:2147483647, �ּ�:-2147483648)" << endl;
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
		cout << endl << "����Ϸ��� �ƹ�Ű�� �Է��ϼ���(����: q)" << endl;
		select = getch();
		if (select == 'q')
			break;
		else
			system("cls");
	}
}
void intALU()
{
	int n, m;	// ������ ���� ����
	int a[MAX_SIZE] = { 0, };	// n�� �������� �ٲ� �� ����
	int b[MAX_SIZE] = { 0, };	// m�� �������� �ٲ� �� ����
	int s[MAX_SIZE] = { 0, }; // ���� ����� �����ϴ� �迭

	// 10���� ���� 2�� �Է� ����
	intInput(n, m);

	// 10������ 2������ ǥ��
	dec_to_bin(n, a);
	dec_to_bin(m, b);

	addition(a, b, s);
	subtraction(a, b, s);
	multiplication(a, b);
	division(a, b);
}
void floatALU()
{
	double n, m;	// ������ ���� �Ǽ�
	int a[MAX_SIZE] = { 0, };
	int b[MAX_SIZE] = { 0, };
	int c[MAX_SIZE] = { 0, };	// ���� ����� �����ϴ� �迭

	// 10���� �Ǽ� 2�� �Է� ����
	floatInput(n, m);


	// 10������ IEEE754ǥ������ ǥ��
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
		cout << "0���� ���� �� �����ϴ�" << endl;
		return;
	}
	fdivision(a, b, c);
	fbin_to_dec(c);
}
void intInput(int& n, int& m)
{
	while (1) {
		cout << "�� 2���� ���� �Է� : ";
		cin >> n >> m;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "�ٽ� �Է��ϼ��� (�ִ�:2147483647, �ּ�:-2147483648)" << endl;
			continue;
		}
		else
			break;
	}
}
void floatInput(double& n, double& m)
{
	while (1) {
		cout << "�� 2���� �Ǽ� �Է� : ";
		cin >> n >> m;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "�ٽ� �Է��ϼ��� (�ִ�:2147483647, �ּ�:-2147483648)" << endl;
			continue;
		}
		else
			break;
	}
}


void twosComplement(int* n, int bit)
{
	// 1�� ����
	for (int i = 0; i < bit; i++)
	{
		n[i] = 1 ^ n[i];
	}
	// 2�� ����
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

	// ��ȣ üũ
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

	// ������ ��� 2�� ������ ǥ��
	if (!flag)
		twosComplement(bin, bit);
}
int bin_to_dec(int* bin, int bit)
{	// �迭 ���� ����X
	int* bin2 = new int[bit];
	for (int i = 0; i < bit; i++)
	{
		bin2[i] = bin[i];
	}

	int dec = 0;
	bool flag = true;
	if (bin2[bit - 1]) // ������ ��� 2�Ǻ��� ������
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
			v = c; // ����ĳ�� ����
		}
	}

	// �÷��� ��
	s = bin3[bit - 1];
	v = v ^ c; // �����÷ο�, v�÷��״� ����ĳ���� �ܺ�ĳ���� XOR
	z = 1;
	for (int i = 0; i < bit; i++)
	{
		if (bin3[i]) {	// NOR����, �迭�� ��簪�� 0�̸� z�÷��״� 1
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
		if (i % 4 == 0 && i != bit) // 28�϶�, 0�϶�
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
	{ // flag�� 1�̸� left
		t = bin[bit - 1];
		for (int i = MAX_SIZE - 1; i > 0; i--)
		{
			bin[i] = bin[i - 1];
		}
		bin[0] = 0;
	}
	else
	{ // flag�� 0�̸� right
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
	// return -> ���� ����Ʈ �� ���� ���� ��Ʈ[31]��,
	// ������ ����Ʈ �� ���� ������ ��Ʈ[0]�� ����
	return t;
}