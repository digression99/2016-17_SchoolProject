#include "Template_LinkedList.h"
#include "SkipList.h"

int main()
{
	SkipList testobj;
	int data;
	int check;

	for (;;)
	{
		cout << "�޴� ���� : 1.�Է� 2.��ġ 3.���� : ";
		cin >> check;

		switch (check)
		{
		case 1:
			cout << "���� �������� �Է��Ͻʽÿ�. : ";
			cin >> data;
			testobj.dataInsert(data);
			testobj.dataDisplay();
			break;
		case 2:
			cout << "ã�� �������� �Է��Ͻʽÿ�. : ";
			cin >> data;
			if (testobj.dataSearch(data) != NULL)
			{
				cout << "�����Ͱ� �ֽ��ϴ�." << endl;
			}
			else
			{
				cout << "�����Ͱ� �����ϴ�." << endl;
			}
			break;
		case 3:
			return 0;
		}
		
		/*cout << "���� �������� �Է��Ͻʽÿ�(����� 0) : ";
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