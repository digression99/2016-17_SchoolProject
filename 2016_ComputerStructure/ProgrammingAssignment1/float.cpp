#include "ALU.h"
using namespace std;

void ieee(double a, int * arr) {

	int count = 0;

	int b[130] = { 0 };
	int c[23] = { 0 };

	int s[1] = { 0 };
	int e[8] = { 0 };
	int m[23] = { 0 };

	if (a < 0) {
		s[0] = 1;
		a = -a;
	}

	//정수부의 2진수화
	fdec_to_bin1(a, b);
	//소수부의 2진수화
	fdec_to_bin2(a - floor(a), c);

	int j = 0;
	//정수부 2진수를 가수배열에 대입
	if (a == 1) {
		count = 0;
		for (int i = 0; i < 23; i++) {
			m[i] = 0;
		}
	}
	else if (a > 1) {
		for (int i = 129; i >= 0; i--)
		{
			if (b[i] == 1) {
				count = i;

				if (count == 0)
				{
					break;
				}

				for (j = 0; j < 23; j++)
				{
					m[j] = b[i - 1];
					if (i == 1)
						break;
					i--;
				}
				break;
			}
		}
		//소수부 대입
		if (count <= 22) {
			for (int i = 0; i < 23 - count; i++) {
				if (count == 0 && i == 0)
				{
					m[0] = c[i];
					i++;
				}
				m[j + 1] = c[i];
				j++;
			}
		}
	}
	else {
		//입력 실수의 절댓값이 1미만일 때
		int i;
		for (i = 0; i < 23; i++) {
			if (c[i] == 1) {
				count = -(i + 1);
				break;
			}
		}
		for (j = 0; j<23; j++) {
			m[j] = c[i + 1];
			i++;
			if (i == 22)
				break;
		}
	}
	if (a == 0) {      //입력 값이 0인 경우 지수, 가수 비트를 모두 0으로 변경
		s[0] = { 0 };
		for (int k = 0; k < 8; k++) {
			for (int l = 0; l < 8; l++)
				e[k] = 0;
		}
		for (int k = 0; k < 23; k++) {
			for (int l = 0; l < 23; l++)
				m[k] = 0;
		}
	}
	else {

		//지수비트 표기(지수부는 127 바이어스이므로 127+지수를 2진수화한 값)
		fdec_to_bin1(127 + count, e);
	}

	for (int i = 0; i < 32; i++) {
		arr[i] = s[0];
		if (i >= 1 && i < 9) {
			arr[i] = e[8 - i];
		}
		else if (i >= 9) {
			arr[i] = m[i - 9];
		}
	}

	cout << "IEEE표준 표기 입니다." << endl;
	for (int i = 0; i < 32; i++) {
		cout << arr[i];
		if (i == 0)
			cout << " ";
		if (i == 8)
			cout << " ";
		if (i == 31)
			cout << " ";
	}
	cout << endl;
}
void fdec_to_bin1(double num, int* bin) {
	num = floor(num);
	if (num >= 1) {
		for (int i = 0; num > 0; i++) {
			if (floor(num / 2) * 2 == num)
				bin[i] = 0;
			else
				bin[i] = 1;
			num = floor(num / 2);
		}
	}
}
void fdec_to_bin2(double num, int* bin) {
	for (int i = 0; i < 23; i++) {
		bin[i] = int(num * 2);
		num = num * 2 - bin[i];
	}
}

void fbin_to_dec(int* ieee) {
   bool flag = true;
   for (int i = 0; i < MAX_SIZE; i++)
   {
      if (ieee[i])
      {
         flag = false;
         break;
      }
   }
   if (flag)
   {
      cout << "0" << endl;
      return;
   }

   double a = 0, b = 0, sum = 0;
   for (int i = 1; i < 9; i++) {   //지수 비트 10진수화
      a += ieee[i] * pow(2, (8 - i));
   }
   for (int i = 9; i < 31; i++) {   //가수 비트 10진수화
      b += ieee[i] * pow(2, -(i - 8));
   }
   sum = (b + 1)*pow(2, a - 127);
   cout << sum << endl;
}


void faddition(int* a, int* b, int* c)
{
	// adder_subtracter(), twosComplement()함수 등은
	// 인덱스가 0인 방이 오른쪽에 위치한다고 가정하지만,
	// 32비트로 표현한 실수의 배열은 인덱스가 0인 방이 왼쪽에 위치
	// i가 증가하면 j는 감소하는 방식으로 표현

	cout << "=======================================덧셈=====================================" << endl;

	// 지수부
	int am[MF] = { 0 };
	int bm[MF] = { 0 };
	int cm[MF] = { 0 };
	// 가수부
	// 가수의 덧셈에서 carry값과 생략된 1을 표현하기위해 2를 더해줌
	int ae[EF + 2] = { 0 };
	int be[EF + 2] = { 0 };
	int ce[EF + 2] = { 0 };	

	// 초기화
	// 함수의 사용을 위해 역순으로 초기화
	for (int i = 0; i < MAX_SIZE; i++)
	{
		c[i] = 0;
	}
	int j = MF - 1;
	for (int i = 0; i < MF; i++)
	{
		am[j] = a[i + MF_S];
		bm[j] = b[i + MF_S];
		j--;
	}
	ae[EF] = be[EF] = 1;	// 생략된 1
	j = EF - 1;
	for (int i = 0; i < EF; i++)
	{
		ae[j] = a[i + EF_S];
		be[j] = b[i + EF_S];
		j--;
	}

	cout << "1. 초기값" << endl;
	cout << "피가수) 부호 : " << a[0] << ", 지수부 : ";
	arrPrint(am, MF);
	cout << ", 가수부 : (" << ae[EF + 1] << ae[EF] << ".)";
	arrPrint(ae, EF);
	cout << endl << " 가수 ) 부호 : " << b[0] << ", 지수부 : ";
	arrPrint(bm, MF);
	cout << ", 가수부 : (" << be[EF + 1] << be[EF] << ".)";
	arrPrint(be, EF);
	cout << endl << endl;

	bool aZero = true;
	bool bZero = true;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (aZero == true && a[i] != 0)
		{
			aZero = false;
		}
		if (bZero == true && b[i] != 0)
		{
			bZero = false;
		}
	}
	if (aZero||bZero)
	{
		if (aZero) // a가 0
		{
			if (bZero)	// b도 0
			{
				for (int i = 0; i < MAX_SIZE; i++)
				{
					c[i] = 0;
				}
			}
			else // a만 0
			{
				for (int i = 0; i < MAX_SIZE; i++)
				{
					c[i] = b[i];
				}
			}
		}
		else if (bZero)	// b만 0
		{
			for (int i = 0; i < MAX_SIZE; i++)
			{
				c[i] = a[i];
			}
		}
		cout << "2. 결과 값 : ";
		for (int i = 0; i < MAX_SIZE; i++)
		{
			if (i % 4 == 1)
			{
				cout << " ";
			}
			cout << c[i];
		}
		cout << endl << endl;
		cout << "3. 10진수 결과 값 : ";
		return;
	}
	

	// 지수 조정
	adder_subtracter(1, am, bm, cm, true, MF);
	int count = bin_to_dec(cm, MF);
	if (count > 0)	// b + count
	{
		for (int i = 0; i < 8; i++)
		{
			cm[i] = am[i];
		}

		// count만큼 be 우측 쉬프트
		for (int i = 0; i < count; i++)
		{
			shift(be, RIGHT, INIT, EF + 2);
		}

		// 결과 값의 부호 == a의 부호
		c[0] = a[0];
	}
	else if(count < 0)// a + count 
	{	
		for (int i = 0; i < 8; i++)
		{
			cm[i] = bm[i];
		}
		// -count만큼 ae 우측 쉬프트
		for (int i = 0; i < -count; i++)
		{
			shift(ae, RIGHT, INIT, EF + 2);
		}

		// 결과 값의 부호 == b의 부호
		c[0] = b[0];
	}
	else // 두 수의 지수가 같을 때
	{
		for (int i = 0; i < 8; i++)
		{
			cm[i] = am[i];
		}
		// 가수비교
		// 결과값의부호는 가수절댓값 큰값 따라감
		for (int i = 2; i < EF+2; i++)
		{
			if (ae[i] == be[i])
			{
				continue;
			}
			else
			{
				if (ae[i] > be[i])
				{
					c[0] = a[0];
				}
				else
					c[0] = b[0];
				break;
			}
		}
	}
	cout << "2. 지수 조정" << endl;
	cout << "피가수) 부호 : " << a[0] << ", 지수부 : ";
	arrPrint(cm, MF);
	cout << ", 가수부 : (" << ae[EF + 1] << ae[EF] << ".)";
	arrPrint(ae, EF);
	cout << endl << " 가수 ) 부호 : " << b[0] << ", 지수부 : ";
	arrPrint(cm, MF);
	cout << ", 가수부 : (" << be[EF + 1] << be[EF] << ".)";
	arrPrint(be, EF);
	cout << endl << endl;

	if (a[0])	// a가 음수
	{
		twosComplement(ae, EF + 2);
	}
	if (b[0])	// b가 음수
	{
		twosComplement(be, EF + 2);
	}

	cout << "3. 가수의 보수표현 (음수)" << endl;
	cout << "피가수) 부호 : " << a[0] << ", 지수부 : ";
	arrPrint(cm, MF);
	cout << ", 가수부 : (" << ae[EF + 1] << ae[EF] << ".)";
	arrPrint(ae, EF);
	cout << endl << " 가수 ) 부호 : " << b[0] << ", 지수부 : ";
	arrPrint(cm, MF);
	cout << ", 가수부 : (" << be[EF + 1] << be[EF] << ".)";
	arrPrint(be, EF);
	cout << endl << endl;
	
	// 가수 덧셈
	adder_subtracter(0, ae, be, ce, true, EF + 2);
	cout << "4. 가수 덧셈" << endl;
	cout << "  " << ae[EF + 1] << ae[EF] << ".";
	arrPrint(ae, EF);
	cout << endl << " +" << be[EF + 1] << be[EF] << ".";
	arrPrint(be, EF);
	cout << endl << " --------------------------------" << endl;
	cout << "  " << ce[EF + 1] << ce[EF] << ".";
	arrPrint(ce, EF);

	bool z = true;
	for (int i = 0; i < EF+2; i++)
	{
		if (ce[i] == 1)
		{
			z = false;
			break;
		}
	}
	if (z)
	{
		cout << endl << endl;
		cout << "5. 결과 값 : 0";
	}
	else {
		if (ce[EF+1])
		{
			twosComplement(ce, EF+2);
			cout << endl << "  " << ce[EF + 1] << ce[EF] << ".";
			arrPrint(ce, EF);
		}
		cout << endl << endl;
		// 정규화
		j = 0;
		for (int i = EF + 1; i >= 0; i--)
		{
			if (ce[i] == 1)
			{
				count = j;
				break;
			}
			j++;
		}

		j = EF - count;
		for (int i = 0; i < EF; i++)
		{
			c[i + EF_S] = ce[j];
			if (j == 0)
			{
				break;
			}
			j--;

		}

		if (count != 1)
		{
			// 지수-(count-1)
			int cm2[MF] = { 0 };
			dec_to_bin(count - 1, cm2, MF);
			adder_subtracter(1, cm, cm2, cm, true, MF);
		}

		j = MF - 1;
		for (int i = 0; i < MF; i++)
		{
			c[i + MF_S] = cm[j];
			j--;
		}

		cout << "5. 정규화(결과) : ";
		for (int i = 0; i < MAX_SIZE; i++)
		{
			if (i % 4 == 1)
			{
				cout << " ";
			}
			cout << c[i];
		}
	}
	cout << endl << endl;
	cout << "6. 10진수 결과 값 : ";
}
void fsubtraction(int* a, int* b, int* c)
{
	// 덧셈함수와 기본로직 동일
	// 가수부의 덧셈만 뺄셈으로

	cout << "=======================================뺄셈=====================================" << endl;

	// 지수부
	int am[MF] = { 0 };
	int bm[MF] = { 0 };
	int cm[MF] = { 0 };
	// 가수부
	// 가수의 뺄셈에서 carry값과 생략된 1을 표현하기위해 2를 더해줌
	int ae[EF + 2] = { 0 };
	int be[EF + 2] = { 0 };
	int ce[EF + 2] = { 0 };

	// 초기화
	// 함수의 사용을 위해 역순으로 초기화
	for (int i = 0; i < MAX_SIZE; i++)
	{
		c[i] = 0;
	}
	int j = MF - 1;
	for (int i = 0; i < MF; i++)
	{
		am[j] = a[i + MF_S];
		bm[j] = b[i + MF_S];
		j--;
	}
	ae[EF] = be[EF] = 1;	// 생략된 1
	j = EF - 1;
	for (int i = 0; i < EF; i++)
	{
		ae[j] = a[i + EF_S];
		be[j] = b[i + EF_S];
		j--;
	}

	cout << "1. 초기값" << endl;
	cout << "피감수) 부호 : " << a[0] << ", 지수부 : ";
	arrPrint(am, MF);
	cout << ", 가수부 : (" << ae[EF + 1] << ae[EF] << ".)";
	arrPrint(ae, EF);
	cout << endl << " 감수 ) 부호 : " << b[0] << ", 지수부 : ";
	arrPrint(bm, MF);
	cout << ", 가수부 : (" << be[EF + 1] << be[EF] << ".)";
	arrPrint(be, EF);
	cout << endl << endl;

	bool aZero = true;
	bool bZero = true;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (aZero == true && a[i] != 0)
		{
			aZero = false;
		}
		if (bZero == true && b[i] != 0)
		{
			bZero = false;
		}
	}
	if (aZero || bZero)
	{
		if (aZero) // a가 0
		{
			if (bZero)	// b도 0
			{
				for (int i = 0; i < MAX_SIZE; i++)
				{
					c[i] = 0;
				}
			}
			else // a만 0
			{
				for (int i = 0; i < MAX_SIZE; i++)
				{
					c[i] = b[i];
				}
				c[0] = 1;

			}
		}
		else if (bZero)	// b만 0
		{
			for (int i = 0; i < MAX_SIZE; i++)
			{
				c[i] = a[i];
			}
		}
		cout << "2. 결과 값 : ";
		for (int i = 0; i < MAX_SIZE; i++)
		{
			if (i % 4 == 1)
			{
				cout << " ";
			}
			cout << c[i];
		}
		cout << endl << endl;
		cout << "3. 10진수 결과 값 : ";
		return;
	}

	// 지수 조정
	adder_subtracter(1, am, bm, cm, true, MF);
	int count = bin_to_dec(cm, MF);
	if (count > 0)	// b + count
	{
		for (int i = 0; i < 8; i++)
		{
			cm[i] = am[i];
		}

		// count만큼 be 우측 쉬프트
		for (int i = 0; i < count; i++)
		{
			shift(be, RIGHT, INIT, EF + 2);
		}

		// 결과 값의 부호 == a의 부호
		c[0] = a[0];
	}
	else if (count < 0)// a + count 
	{
		for (int i = 0; i < 8; i++)
		{
			cm[i] = bm[i];
		}
		// -count만큼 ae 우측 쉬프트
		for (int i = 0; i < -count; i++)
		{
			shift(ae, RIGHT, INIT, EF + 2);
		}

		// 결과 값의 부호 == b의 반대 부호
		c[0] = b[0]==1?0:1;
	}
	else // 두 수의 지수가 같을 때
	{
		for (int i = 0; i < 8; i++)
		{
			cm[i] = am[i];
		}
		// 가수비교
		// 결과값의부호는 가수절댓값 큰값 따라감
		for (int i = 2; i < EF + 2; i++)
		{
			if (ae[i] == be[i])
			{
				continue;
			}
			else
			{
				if (ae[i] > be[i])
				{
					c[0] = a[0];
				}
				else
					c[0] = b[0];
				break;
			}
		}
	}
	cout << "2. 지수 조정" << endl;
	cout << "피감수) 부호 : " << a[0] << ", 지수부 : ";
	arrPrint(cm, MF);
	cout << ", 가수부 : (" << ae[EF + 1] << ae[EF] << ".)";
	arrPrint(ae, EF);
	cout << endl << " 감수 ) 부호 : " << b[0] << ", 지수부 : ";
	arrPrint(cm, MF);
	cout << ", 가수부 : (" << be[EF + 1] << be[EF] << ".)";
	arrPrint(be, EF);
	cout << endl << endl;

	if (a[0])	// a가 음수
	{
		twosComplement(ae, EF + 2);
	}
	if (b[0])	// b가 음수
	{
		twosComplement(be, EF + 2);
	}

	cout << "3. 가수의 보수표현 (음수)" << endl;
	cout << "피감수) 부호 : " << a[0] << ", 지수부 : ";
	arrPrint(cm, MF);
	cout << ", 가수부 : (" << ae[EF + 1] << ae[EF] << ".)";
	arrPrint(ae, EF);
	cout << endl << " 감수 ) 부호 : " << b[0] << ", 지수부 : ";
	arrPrint(cm, MF);
	cout << ", 가수부 : (" << be[EF + 1] << be[EF] << ".)";
	arrPrint(be, EF);
	cout << endl << endl;

	// 가수 뺄셈
	adder_subtracter(1, ae, be, ce, true, EF + 2);
	cout << "4. 가수 뺄셈" << endl;
	cout << "  " << ae[EF + 1] << ae[EF] << ".";
	arrPrint(ae, EF);
	cout << endl << " -" << be[EF + 1] << be[EF] << ".";
	arrPrint(be, EF);
	cout << endl << " --------------------------------" << endl;
	cout << "  " << ce[EF + 1] << ce[EF] << ".";
	arrPrint(ce, EF);

	bool z = true;
	for (int i = 0; i < EF + 2; i++)
	{
		if (ce[i] == 1)
		{
			z = false;
			break;
		}
	}
	if (z)
	{
		cout << endl << endl;
		cout << "5. 결과 값 : 0";
	}
	else {
		if (ce[EF + 1])
		{
			twosComplement(ce, EF + 2);
			cout << endl << "  " << ce[EF + 1] << ce[EF] << ".";
			arrPrint(ce, EF);
		}
		cout << endl << endl;
		// 정규화
		j = 0;
		for (int i = EF + 1; i >= 0; i--)
		{
			if (ce[i] == 1)
			{
				count = j;
				break;
			}
			j++;
		}

		j = EF - count;
		for (int i = 0; i < EF; i++)
		{
			c[i + EF_S] = ce[j];
			if (j == 0)
			{
				break;
			}
			j--;

		}

		if (count != 1)
		{
			// 지수-(count-1)
			int cm2[MF] = { 0 };
			dec_to_bin(count - 1, cm2, MF);
			adder_subtracter(1, cm, cm2, cm, true, MF);
		}

		j = MF - 1;
		for (int i = 0; i < MF; i++)
		{
			c[i + MF_S] = cm[j];
			j--;
		}

		cout << "5. 정규화(결과) : ";
		for (int i = 0; i < MAX_SIZE; i++)
		{
			if (i % 4 == 1)
			{
				cout << " ";
			}
			cout << c[i];
		}
	}
	cout << endl << endl;
	cout << "6. 10진수 결과 값 : ";
}
void fdivision(int* a, int* b, int* c)
{
	cout << "=======================================나눗셈=====================================" << endl;


	int Abase[8], Bbase[8];
	int ieeeBase[8] = { 1, 1, 1, 1, 1, 1, 1, 0 };
	int Asignif[23], Bsignif[23], Csignif[23];
	int count = 0, count2 = 0;

	for (int i = 0; i < MF; i++)
	{
		Abase[i] = a[MF - i - 1];
		Bbase[i] = b[MF - i - 1];
	}
	adder_subtracter(MINUS, Abase, ieeeBase, Abase, true, MF);
	adder_subtracter(MINUS, Bbase, ieeeBase, Bbase, true, MF);

	adder_subtracter(MINUS, Abase, Bbase, Abase, true, MF);

	for (int i = 0; i < EF; i++)
	{
		Asignif[i] = a[i + 8];
		Bsignif[i] = b[i + 8];
	}

	for (int i = EF - 1; i >= 0; i--)
	{
		if (a[i] == 1)
		{
			Asignif[count++] = 1;
		}
		else
		{
			if (count > 0)
			{
				Asignif[count++] = 0;
			}
		}

		if (b[i] == 1)
		{
			Bsignif[count2++] = 1;
		}
		else
		{
			if (count2 > 0)
			{
				Bsignif[count++] = 0;
			}
		}
	}

	division2(Asignif, Bsignif, EF);

	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (i == 0)
		{
			c[i] = !(a[i] ^ b[i]);
		}
		else if (i >= 1 && i < 9)
		{
			c[i] = Abase[i - 1];
		}
		else
		{
			c[i] = Csignif[i - 9];
		}
	}

}

void division2(int* bin1, int* bin2, int size)
{
	int * M = new int[size];
	int * A = new int[size];
	int * Q = new int[size];
	int * temp = new int[size];

	int i, j;
	int q1 = 0, q31 = 0;	// Q의 1-비트레지스터와 최상위비트
	int sign = 0;	// a의 부호를 저장하는 변수
	int check = 0;	// 제수와 피제수의 부호 체크

	for (i = 0; i < size; i++)
	{
		Q[i] = bin1[i];
		M[i] = bin2[i];
	}

	if (Q[size - 1] == MINUS)	// 피제수가 음수이면 A는 1로 초기화
	{
		for (i = 0; i < size; i++)
		{
			A[i] = 1;
		}
	}
	check = Q[size - 1] ^ M[size - 1]; // 제수와 피제수의 부호가 다르면 check는 1

	for (int i = 0; i < size; i++)
	{
		// 좌측 쉬프트
		q31 = Q[size - 1];
		shift(A, LEFT, !INIT, size);
		shift(Q, LEFT, !INIT, size);
		sign = A[size - 1];
		A[0] = q31;

		for (j = 0; j < size; j++)
		{
			temp[j] = A[j]; // A 복원용
		}

		// A와 M의 부호가 같으면 뺄셈, 다르면 덧셈
		if (sign == M[size - 1])
		{
			// 뺄셈
			adder_subtracter(MINUS, A, M, A, true, size);
		}
		else
		{	// 덧셈
			adder_subtracter(PLUS, A, M, A, true, size);
		}

		// 연산 전후 A의 부호가 같으면 성공, 다르면 실패
		if (sign == A[size - 1] || bin_to_dec(A, size) == 0)	// 성공 or A == 0
		{
			Q[0] = 1;	// Q0을 1로 세트
		}
		else if (sign != A[size - 1])	// 실패
		{
			for (j = 0; j < size; j++)
			{
				A[j] = temp[j];	// 복원
			}
		}
	}
	if (check) // 제수부호와 피제수부호가 다름
	{
		twosComplement(Q, size);	// 결과값의 보수가 몫
	}
}

void fmultiplication(int * a, int * b, int * c)
{ 
	// a : 승수 피승수 결과배열 // 지수 맞추는거 구현

	cout << "=======================================곱셈=====================================" << endl;

	bool flag = true;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (a[i] || b[i])
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		for (int i = 0; i < MAX_SIZE; i++)
		{
			c[i] = 0;
		}
		return;
	}

	int Abase[8] = { 0, }, Bbase[8] = { 0, };
	int ieeeBase[8] = { 1, 1, 1, 1, 1, 1, 1, 0 };
	int Asignif[23], Bsignif[23], Csignif[23];
	int count = 0, count2 = 0;

	for (int i = 0; i < MF; i++)
	{
		Abase[i] = a[MF - i - 1];
		Bbase[i] = b[MF - i - 1];
	}
	adder_subtracter(MINUS, Abase, ieeeBase, Abase, true, MF);
	adder_subtracter(MINUS, Bbase, ieeeBase, Bbase, true, MF);

	adder_subtracter(PLUS, Abase, Bbase, Abase, true, MF);

	for (int i = 0; i < EF; i++)
	{
		Asignif[i] = a[i + 8];
		Bsignif[i] = b[i + 8];
	}

	for (int i = EF - 1; i >= 0; i--)
	{
		if (a[i] == 1)
		{
			Asignif[count++] = 1;
		}
		else
		{
			if (count > 0)
			{
				Asignif[count++] = 0;
			}
		}

		if (b[i] == 1)
		{
			Bsignif[count2++] = 1;
		}
		else
		{
			if (count2 > 0)
			{
				Bsignif[count++] = 0;
			}
		}
	}

	multiplication2(Asignif, Bsignif, Csignif, EF);

	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (i == 0)
		{
			c[i] = !(a[i] ^ b[i]);
		}
		else if (i >= 1 && i < 9)
		{
			c[i] = Abase[i - 1];
		}
		else
		{
			c[i] = Csignif[i - 9];
		}
	}
}

void multiplication2(int * bin1, int * bin2, int * bin3, int size)
{
	int * M, *A, *Q, R[64] = { 0, }; // R:A+Q
	int i;
	int q1 = 0, q31 = 0;	// q1 : 1-비트 레지스터

	M = new int[size];
	A = new int[size];
	Q = new int[size];

	for (i = 0; i < size; i++)
	{
		Q[i] = bin2[i];
		M[i] = bin1[i];
		A[i] = 0;
	}

	for (i = 0; i < size; i++)
	{
		if (q1 == 0)
		{
			if (Q[0] == 1)
			{
				// 뺄셈
				adder_subtracter(MINUS, A, M, A, true, size);
			}
		}
		else if (q1 == 1)
		{
			if (Q[0] == 0)
			{
				// 덧셈
				adder_subtracter(PLUS, A, M, A, true, size);
			}
		}

		// RIGHT 쉬프트.
		q31 = A[0];
		q1 = Q[0];
		shift(A, RIGHT, !INIT, size);
		shift(Q, RIGHT, !INIT, size);
		Q[MAX_SIZE - 1] = q31;
	}
	for (int i = 0; i < size; i++)
	{
		R[i] = Q[i];
		R[size + i] = A[i];
	}

	for (int i = 0; i < size; i++)
	{
		bin3[i] = Q[i];
	}

	delete[] M;
	delete[] Q;
	delete[] A;
}

int bin_to_dec2(int* bin, int bit) // 부호X
{
	int* bin2 = new int[bit];
	for (int i = 0; i < bit; i++)
	{
		bin2[i] = bin[i];
	}

	int dec = 0;
	bool flag = true;
	for (int i = 0; i < bit; i++)
	{
		dec += bin2[i] * pow(2, i);
	}

	delete[] bin2;

	return dec;
}
void arrPrint(int* a, int n)
{
	int j = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		if (j % 4 == 0 && j != 0)
		{
			cout << " ";
		}
		cout << a[i];
		j++;
	}
}