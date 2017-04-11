//
// 사용자로부터 임의의 데이터 셋(양의 정수)을 입력받고,
// 각 알고리즘을 수행한 결과,
// 수행 시간 및 적중률 분석.
// 입력 데이터 개수와 세트당 슬롯의 개수는
// 사용자가 프로그램을 실행하면서 임의로 선택할 수 있도록.
// 결과, 수행시간, 적중률 비교 분석

#pragma warning(disable:4996)

#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <conio.h>
using namespace std;

const int ARR_NUM = 4;

double LRU(vector<int> & c, vector<int> & cnt, vector<int> & d);
double FIFO(deque<int> & cache, vector<int> & data, int slotNum);
double LFU(deque<int> & cache, vector<int> & count, vector<int> & data);
double random(vector<int> & cache, vector<int> & data);
void initialization(vector<int> & c, vector<int> & cnt, vector<int> & data, int & sn);
void run();
double getFuncTime(double(*fp)(void *, void *, void *));


int main(int argc, const char * argv[])
{
	char key;
	do
	{
		system("cls");
		run();
		cout << "Press any key to continue. (END : q)" << endl;
		key = getch();
	} while (key != 'q');

	return 0;
}

void run()
{
	int sn;
	double hitRatio = 0.0;
	vector<int> cache;
	vector<int> count;
	vector<int> data;
	deque<int> q;
	double timeArr[ARR_NUM];
	double ratioArr[ARR_NUM];
	clock_t start, end;
	char name[10];

	initialization(cache, count, data, sn);
	cout << endl;

	for (int i = 0; i < ARR_NUM; ++i)
	{
		start = clock();
		switch (i + 1)
		{
		case 1:
			hitRatio = LRU(cache, count, data);
			strcpy(name, "LRU");
			break;
		case 2:
			hitRatio = FIFO(q, data, sn);
			strcpy(name, "FIFO");
			break;
		case 3:
			hitRatio = LFU(q, count, data);
			strcpy(name, "LFU");
			break;
		case 4:
			hitRatio = random(cache, data);
			strcpy(name, "random");
			break;
		}
		end = clock();
		cout << "time(" << name << ") : " << (timeArr[i] = (end - start)) << endl;
		cout << "hitRatio(" << name << ") : " << (ratioArr[i] = hitRatio) << endl;
		cout << endl;
	}
}

void initialization(vector<int> & c, vector<int> & cnt, vector<int> & d, int & sn)
{
	int dn;

	srand((unsigned)time(nullptr));

	while (1) {
		cout << "Data Number, Slot Number : "; // 데이터 개수와 슬롯 개수를 입력받는다.
		cin >> dn >> sn;
		
		if (cin.fail() || dn < 0 || sn < 0)
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Enter a positive integer." << endl;
			continue;
		}
		else
			break;
	}

	c.assign(sn, -1);
	cnt.assign(sn, 0);
	d.assign(dn, 0);

	for (int i = 0; i < dn; ++i)
	{
		while (1) {
			//cout << "data[" << i + 1 << "] :"; // 각 데이터를 입력받는다.
			//cin >> d[i];
			d[i] = rand() % 10 + 1;
			if (cin.fail() || d[i] < 0)
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Enter a positive integer." << endl;
				continue;
			}
			else
				break;
		}
	}
}

double random(vector<int> & cache, vector<int> & data)
{
	int hit = 0, cNum = 0;
	bool isHit;

	for (int i = 0; i < data.size(); ++i) // 데이터 개수만큼 반복한다.
	{
		isHit = false;
		for (int j = 0; j < cNum; ++j)
		{
			if (data[i] == cache[j]) // 슬롯에 데이터가 있으면 적중.
			{
				hit++;
				isHit = true;
				break;
			}
		}

		if (!isHit)
		{
			if (cNum < cache.size()) // 슬롯이 꽉차지 않았다면
				cache[cNum++] = data[i]; // 남는 슬롯에 데이터를 넣는다.
			else // 슬롯이 꽉찼다면
				cache[rand() % cache.size()] = data[i]; // 랜덤으로 넣는다.
		}
	}
	return double(hit) / data.size();
}


double LFU(deque<int> & cache, vector<int> & count, vector<int> & data)
{
	int hit = 0, cNum = 0, minIdx = 0;
	bool isHit = false;
	deque<int>::iterator it;

	cache.clear();
	it = cache.begin();

	for (int i = 0; i < data.size(); ++i)
	{
		while (it != cache.end())
		{
			if (data[i] == *it++) // 슬롯에 데이터가 있으면 적중
			{
				hit++;
				isHit = true;

				count[it - cache.begin() - 1]++; // 그 데이터의 카운트를 하나 올린다.

				break;
			}
		}

		if (!isHit) // 데이터가 없다면
		{
			if (cNum < count.size()) // 슬롯에 빈자리가 있다면 그냥 넣는다.
			{
				cache.push_back(data[i]);
				count[cNum++] = 1;
			}
			else // 슬롯에 빈자리가 없다면
			{
				for (int j = 0; j < count.size(); ++j) // 가장 적게 사용된 데이터를 찾는다.
				{
					if (count[j] < count[minIdx])
					{
						minIdx = j;
					}
				}
				cache.erase(cache.begin() + minIdx); // 그 데이터를 지운다.
				count.erase(count.begin() + minIdx); // 카운트도 지운다.
				cache.push_back(data[i]); // 그리고 데이터를 넣는다.
				count.push_back(1); // 카운트도 넣는다.
			}
		}
		isHit = false;
		it = cache.begin();
		minIdx = 0;
	}

	return double(hit) / data.size();
}

double FIFO(deque<int> & cache, vector<int> & data, int slotNum)
{
	int hit = 0, cNum = 0;
	bool isHit = false;
	deque<int>::iterator it;

	cache.clear();
	it = cache.begin();

	for (int i = 0; i < data.size(); ++i)
	{
		while (it != cache.end())
		{
			if (data[i] == *it++) // 안에 데이터가 있으면 적중.
			{
				hit++;
				isHit = true;
				break;
			}
		}

		if (!isHit)
		{
			if (cNum < slotNum) // 슬롯에 빈자리가 있다면
			{
				cache.push_back(data[i]);
				cNum++;
			}
			else // 슬롯에 빈자리가 없다면
			{
				cache.pop_front(); // 맨 앞의 데이터를 제거한다.
				cache.push_back(data[i]); // 그리고 지금 데이터를 넣는다.
			}
		}
		isHit = false;
		it = cache.begin();
	}

	return double(hit) / data.size();
}


double LRU(vector<int> & cache, vector<int> & count, vector<int> & data)
{ // least recently used
	int hit = 0, maxIdx = 0, cNum = 0;
	bool isHit = false;
	// 넣거나 히트거나 둘중에 하나
	for (int i = 0; i < data.size(); ++i)
	{
		for (int j = 0; j < cNum; ++j)
		{
			if (data[i] == cache[j]) // 데이터가 있으면 적중.
			{
				hit++;
				count[j] = 0; // 적중됐으면 카운트를 0으로 만든다.
				isHit = true;
				break;
			}
		}

		if (!isHit) // 데이터를 찾지 못했다면
		{
			if (cNum < cache.size()) // 슬롯에 빈자리가 있다면
			{
				cache[cNum] = data[i];
				count[cNum] = 0;
				cNum++;
			}
			else
			{ // 꽉 찼다면
				for (int j = 0; j < count.size(); ++j) // 가장 카운트가 큰 변수를 찾는다.
				{
					if (count[maxIdx] < count[j])
						maxIdx = j;
				}
				cache[maxIdx] = data[i]; // 거기에 데이터를 넣는다.
				count[maxIdx] = 0; // 그 데이터의 카운트는 0으로 해준다.
			}
		}

		for (int j = 0; j < cNum && j != i; ++j) // 한 번 처리할 때마다 모든 카운트를 증가시킨다.
		{
			count[j]++;
		}
		isHit = false;
		maxIdx = 0;
	}
	return double(hit) / data.size();
}