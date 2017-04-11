#include "Template_LinkedList.h"
#include <math.h>

//template <typename T>
//class SkipList
//{
//private:
//	LinkedList<T> root;
//	int level;
//	int nodeNum;
//public:
//	// ������ �߰�
//	// ������ ����
//	// ������ �˻�
//	// ������ �ϳ� ����� �Լ� �ʿ�.(�����Լ�)
//	// ���� �ϳ� ����.
//	// ��� �ϳ� ���� -> ��ũ�帮��Ʈ�� �Լ� �̿�.
//	// ��� ���÷���.
//	//
//	//
//	//
//	//
//	// ������ �˻� : ���� Ű���� �����Ͱ��� �������� ����.
//	// �˻��� �����Ͱ��� ���� ������ ��������
//	// �� �Ʒ� ������ �ִ� ����� �ּҸ� ������.
//	//
//	// ������ �߰� : �����Ͱ� �ϳ� ���� ��, �� �� ���� ��, �� �� ���� ���� �����Ѵ�.
//	// �����Ϳ� ������ ���̿� �� ���� �����Ͱ� ������
//	// �ϳ��� �����͸� ���� �ø���.
//	//
//	// ������ ���� : �� �ٿ� �ִ� ��� ���� �����͸� �����ϰ�
//	// ��尡 ���Ͽ� �ΰ��� ���´ٸ� ��ü������ Ʈ���� ������
//	// -> ���� ������ �ö󰡸鼭 ������ �ǳ� Ȯ��.
//	//
//	//
//	//
//	//
//	//
//	//
//
//
//}; ���� int skiplist�� ������. �׸��� ���ø�����.

class SkipList
{
private:
	LinkedList<LinkedList<int> > root;
	int level;
	int nodeNum;
public:
	SkipList() : level(0), nodeNum(0) {};
	~SkipList();
	Node<int> *dataSearch(int &data);
	Node<int> *insertNewData(LinkedList<int> &lp, int &item);
	int dataInsert(int &item);
	void dataDisplay();
	//Node<int> *compareListData(LinkedList<int> &lp, int &item, bool &wParam);
	//int dataDelete(int &item);
};

void SkipList::dataDisplay()
{
	int i = 1;
	this->root.setCur(this->root.getHead()->getNext());

	while (this->root.getCur() != this->root.getTail())
	{
		cout << "level : " << i++ << endl;
		this->root.getCur()->getData().display();
		this->root.setCur(this->root.getCur()->getNext());
	}
	return;
}

SkipList::~SkipList()
{}

//Node<int> *compareListData(LinkedList<int> &lp, int &item, int &wParam)
//� ��ũ�帮��Ʈ���� ��ġ�� ������ �����Ѵ�.
// ���� ���� ���� ��� �� ã�� �����Ͱ� ���ٸ�
// ������ �ּҸ� �����Ѵ�.
//wParam�� true�̸� ã�� ��. false�̸� ������ �ּҸ� ������ ��.

Node<int> *SkipList::dataSearch(int &item)
{
	Node<int> *searchNode;
	//LinkedList<int> *searchList;
	bool check;
	//��ġ��忡 ù��° ��ũ�帮��Ʈ�� ù��° ��带 �����Ѵ�.
	searchNode = this->root.getHead()->getNext()->getData().getHead()->getNext();
	this->root.setCur(this->root.getHead()->getNext());// ù ����Ʈ�� ����Ű�� �Ѵ�.

	while (searchNode != NULL)
	{
		/*searchNode = this->root.getHead()->getNext()->getData().getHead()->getNext();
		this->root.setCur(this->root.getHead()->getNext());*/
		//searchList = &this->root.getHead()->getNext()->getData();
		if (searchNode->getData() == item)
		{
			return searchNode;
		}
		else if (searchNode->getNext() != this->root.getCur()->getData().getTail())
		{ // ������ ���ٸ� ��¿ ���ΰ�. -> ��ũ�帮��Ʈ�� ����ϰ� �� ���ϰ� ���Ѵ�.
			//���� �ƴ϶�� ������ ū���� �˻��Ѵ�.
			// ���� �����ؾ�.
			if (searchNode->getData() < searchNode->getNext()->getData())
			{
				searchNode = searchNode->getNext(); // ���� ��尡 �ִٸ� �������� �̵��Ѵ�.
				continue;
			}
		} 
		searchNode = searchNode->getDown(); // linkNode�� ������ �ִ�.
		this->root.setCur(this->root.getCur()->getNext()); // ���� ����Ʈ�� �Ѿ��.
	}
	return NULL; // �����Ͱ� ������ �ΰ��� ��ȯ�Ѵ�.

	//this->root.setCur(this->root.getHead()->getNext());

	//while (this->root.getCur() != this->root.getTail())
	//{ //��带 Ÿ���� ��ũ�帮��Ʈ�� Ÿ�� �ȵȴ�. down�� NULL�� ������.
	//	temp = compareListData(this->root.getCur()->getData(), item, check);
	//	if (check == true)
	//	{
	//		return temp;
	//	}
	//	else
	//	{
	//		// �Ʒ��� �������� �Ѵ�.
	//		this->root.setCur(this->root.getCur()->getNext());
	//	}
	//}
	//// �����Ͱ� ���ٸ� �ΰ��� ��ȯ�Ѵ�.
	//return NULL;

	/*this->root.getTail()->getPrev()->getData().setCur(
		this->root.getTail()->getPrev()->getData().getHead()->getNext());

	while (this->root.getTail()->getPrev()->getData().getCur() !=
		this->root.getTail()->getPrev()->getData().getTail())
	{
		
	}
	return this->root.getHead()->getNext()->getData().getHead()->getNext();*/
}

//Node<int> *SkipList::compareListData(LinkedList<int> &lp, int &item, bool &check)
//{
//	lp.setCur(lp.getHead()->getNext());
//
//	while (lp.getCur() != lp.getTail())
//	{
//		if (lp.getCur()->getData() == item)
//		{
//			check = true;
//			return lp.getCur();
//		}
//		else if (lp.getCur()->getData() < lp.getCur()->getNext()->getData())
//		{
//			lp.setCur(lp.getCur()->getNext());
//		}
//	}
//	check = false;
//	return lp.getTail()->getPrev();// item�� ��� ��庸�� Ŭ �� ������ ����� �ּҸ� ����.
//}

int SkipList::dataInsert(int &item)
{
	if (this->dataSearch(item) != NULL)
	{
		return 0;
	}

	//if (this->root.getTail()->getPrev()->getData().linearSearchUnique(item) != NULL)
	//{ // �̰��� ��ġ �������� �ٲ۴�.
	//	return 0;
	//}

	if (this->level == 0)
	{
		LinkedList<int> obj;
		obj.appendFromTail(item);
		this->root.appendFromTail(obj);
		this->level++;
		this->nodeNum++;
		return 1;
	}
	else if (this->level == 1)
	{ //�� �Ʒ� ��嵵 ������Ѿ� �ǰ� �� ��� �� ũ�Ⱑ ū ���� ���� �ξ�� �Ѵ�.(���� �׷� �ʿ�� ������ �ϴ���.)
		LinkedList<int> obj;
		Node<int> *temp;
		 // ���� ������.
		temp = obj.appendFromTail(
			this->root.getHead()->getNext()->getData().getHead()->getNext()->getData());
		cout << "data : " << temp->getData() << endl;

		obj.appendFromTail(item); // �ϴ� ���⿡ ������ �����͸� �����Ѵ�.
		// �����ϰ� ���ؼ� ���� ���� ������ �־�� ������ ���Ѵ�.
		if (this->root.getTail()->getPrev()->getData().getTail()->getPrev()->getData() < item)
		{ // ó�� ����Ʈ�� ù ����� �����Ͱ� �����ۺ��� �۴ٸ�
			//cout << "original data : " << this->root.getHead()->getNext()->getData().getHead()->getNext()->getData() << endl;

			this->root.getHead()->getNext()->getData().getHead()->getNext()->setData(item);

			//this->root.getTail()->getData().getTail()->getPrev()->setData(item);
			//cout << "data2 : " << this->root.getHead()->getNext()->getData().getHead()->getNext()->getData() << endl;
		} // �� �������� �������� ���������� �����Ѵ�. 
		this->root.appendFromTail(obj);

		this->root.getTail()->getData().linkNode(
			this->root.getHead()->getNext()->getData().getHead()->getNext(), // ù ����Ʈ�� ù���.
			this->root.getTail()->getPrev()->getData().linearSearchUnique(
			this->root.getHead()->getNext()->getData().getHead()->getNext()->getData()));
		// ��° ����Ʈ���� ù° �����Ϳ� �����Ͱ� �����Ѵ�.
		// ù° ���� ��° ��带 �����Ѵ�. ( ���� �Ʒ��� �����Ѵ�. )
		this->level++;
		this->nodeNum += 2;
		return 1;
	}
	else if (this->root.getTail()->getPrev()->getData().getLength() + 1 <= 
		pow((double)2, this->level - 1))
	{ // �����ۺ��� ���� ��ġ�� ã�Ƽ� �װ��� �������� ���� �ִ´�.

		/*LinkedList<int> obj;
		int temp = pow(2, this->level - 1);
		cout << "temp : " << temp << endl;*/
		// �������� ����ְ� ��带 ������Ѿ� �Ѵ�...
		//////
		// ���⼭ ��ũ���� �ʿ����. �Ʒ��� �������� �� �ƴϱ� ������.
		
		this->insertNewData(this->root.getTail()->getPrev()->getData(), item);
		// �� �� ����Ʈ�� �׳� ��� �ϳ��� �ִ´�.

		//this->root.getTail()->getPrev()->getData().setCur(
		//	this->root.getTail()->getPrev()->getData().getTail()->getPrev());

		//while (this->root.getTail()->getPrev()->getData().getCur() != 
		//	this->root.getTail()->getPrev()->getData().getTail())
		//{
		//	if (this->root.getTail()->getPrev()->getData().compareNodeData(
		//		this->root.getTail()->getPrev()->getData().getCur()->getData(), item) == 0)
		//	{
		//		this->root.getTail()->getPrev()->getData().insertBefore(
		//			this->root.getTail()->getPrev()->getData().getCur(), item);
		//		return 1;
		//	}
		//	this->root.getTail()->getPrev()->getData().setCur(
		//		this->root.getTail()->getPrev()->getData().getCur()->getNext());
		//}
		////��� �� �Լ�.

		//this->root.getTail()->getPrev()->getData().appendFromTail(item); // �������� ���� ũ�ٸ� ���� �ִ´�.
		//////
		this->nodeNum++;

		return 1;
	}
	else
	{ // ���� ���� ���ο� ������ �ִ´�. ������ ������ ���� ���Ѵ�.-> ���� �ִ� �͵��� ��� �����Ѵ�.
		LinkedList<int> obj;
		//���� ������ ����Ʈ�� cur�� ����.
		this->root.getTail()->getPrev()->getData().setCur(
			this->root.getTail()->getPrev()->getData().getHead()->getNext());

		while (this->root.getTail()->getPrev()->getData().getCur() != 
			this->root.getTail()->getPrev()->getData().getTail())
		{// ��ũ��带 �и��� �Ѵ�...
			Node<int> *temp;
			//��ũ���� ����带 ������, ���߿� ��ģ��.
			temp = obj.appendFromTail(this->root.getTail()->getPrev()->getData().getCur()->getData());
			// obj�� �����͸� �߰��Ѵ�. �׸��� ���� ���� // �տ����� ���� �־�� �Ѵ�.
			obj.linkNode(this->root.getTail()->getPrev()->getData().getCur(), temp);

			cout << "temp�� up : " << temp->getUp() << endl;
			cout << "root�� down : " << this->root.getTail()->getPrev()->getData().getCur()->getDown() << endl;

			//obj.linkNode(obj.appendFromTail(
			//	this->root.getTail()->getPrev()->getData().getCur()->getData()),
			//	this->root.getTail()->getPrev()->getData().getCur()); // ���� �ִ� ��� �����͸� �ִ´�. �׸���
			//// ���� ���� ���� ���� ��带 �����Ų��.

			this->root.getTail()->getPrev()->getData().setCur(
				this->root.getTail()->getPrev()->getData().getCur()->getNext()); // �������� �̵��Ѵ�.
		} // while : tail ����Ʈ�� ��� ��带 �����Ѵ�.
		//���ο� ��带 �߰��ϰ�, ���� ���� ��� �����Ѵ�.
		// �� �����͸� ������ �ڸ��� �ְ� �����ؾ� �Ѵ�.
		this->insertNewData(obj, item);
		this->root.appendFromTail(obj);
		//this->insertNewData(this->root.appendFromTail(obj)->getData(), item);
		// �Լ��ȿ� �Լ��� ������ ���� ª�������� ���� �װ��� �ߴ����� �˱Ⱑ ��ƴ�.
		//obj�� ����Ʈ�� �־�� �ȴ�...

		//this->root.appendFromTail(obj);

		this->level++;
		this->nodeNum += obj.getLength();

		return 1;
	} // else
}

Node<int> *SkipList::insertNewData(LinkedList<int> &lp, int &item)
{
	lp.setCur(lp.getHead()->getNext());

	while (lp.getCur() != lp.getTail())
	{
		if (lp.compareNodeData(lp.getCur()->getData(), item) == 0)
		{
			return lp.insertBefore(lp.getCur(), item);
		}
		lp.setCur(lp.getCur()->getNext());
	}
	return lp.appendFromTail(item);
}