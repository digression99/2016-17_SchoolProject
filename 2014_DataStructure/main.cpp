#include "Template_LinkedList.h"
#include "SkipList.h"

int main()
{
	SkipList testobj;
	int data;
	int check;

	for (;;)
	{
		cout << "메뉴 선택 : 1.입력 2.서치 3.종료 : ";
		cin >> check;

		switch (check)
		{
		case 1:
			cout << "넣을 정수값을 입력하십시오. : ";
			cin >> data;
			testobj.dataInsert(data);
			testobj.dataDisplay();
			break;
		case 2:
			cout << "찾을 정수값을 입력하십시오. : ";
			cin >> data;
			if (testobj.dataSearch(data) != NULL)
			{
				cout << "데이터가 있습니다." << endl;
			}
			else
			{
				cout << "데이터가 없습니다." << endl;
			}
			break;
		case 3:
			return 0;
		}
		
		/*cout << "넣을 정수값을 입력하십시오(종료는 0) : ";
		cin >> data;

		if (data == 0)
		{
			break;
		}

		testobj.dataInsert(data);
		testobj.dataDisplay();*/
	}

	return 0;
}