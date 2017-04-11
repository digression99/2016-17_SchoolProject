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
//	// 데이터 추가
//	// 데이터 삭제
//	// 데이터 검색
//	// 레벨을 하나 만드는 함수 필요.(내부함수)
//	// 레벨 하나 삭제.
//	// 노드 하나 삭제 -> 링크드리스트의 함수 이용.
//	// 노드 디스플레이.
//	//
//	//
//	//
//	//
//	// 데이터 검색 : 먼저 키값과 데이터값을 구별하지 말자.
//	// 검색은 데이터값을 따라 밑으로 내려가서
//	// 맨 아래 레벨에 있는 노드의 주소를 보낸다.
//	//
//	// 데이터 추가 : 데이터가 하나 있을 때, 두 개 있을 때, 세 개 있을 때를 구별한다.
//	// 데이터와 데이터 사이에 두 개의 데이터가 있으면
//	// 하나의 데이터를 위로 올린다.
//	//
//	// 데이터 삭제 : 그 줄에 있는 모든 같은 데이터를 삭제하고
//	// 노드가 만일에 두개만 남는다면 전체적으로 트리를 재조정
//	// -> 상위 레벨로 올라가면서 절반이 되나 확인.
//	//
//	//
//	//
//	//
//	//
//	//
//
//
//}; 먼저 int skiplist를 만들자. 그리고 템플릿으로.

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
//어떤 링크드리스트에서 서치의 로직을 실행한다.
// 현재 노드와 다음 노드 중 찾는 데이터가 없다면
// 내려갈 주소를 리턴한다.
//wParam이 true이면 찾은 것. false이면 내려갈 주소를 리턴한 것.

Node<int> *SkipList::dataSearch(int &item)
{
	Node<int> *searchNode;
	//LinkedList<int> *searchList;
	bool check;
	//서치노드에 첫번째 링크드리스트의 첫번째 노드를 대입한다.
	searchNode = this->root.getHead()->getNext()->getData().getHead()->getNext();
	this->root.setCur(this->root.getHead()->getNext());// 첫 리스트를 가리키게 한다.

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
		{ // 다음이 없다면 어쩔 것인가. -> 링크드리스트를 기억하고 그 테일과 비교한다.
			//끝이 아니라면 나보다 큰가를 검사한다.
			// 여기 수정해야.
			if (searchNode->getData() < searchNode->getNext()->getData())
			{
				searchNode = searchNode->getNext(); // 다음 노드가 있다면 다음으로 이동한다.
				continue;
			}
		} 
		searchNode = searchNode->getDown(); // linkNode에 문제가 있다.
		this->root.setCur(this->root.getCur()->getNext()); // 다음 리스트로 넘어간다.
	}
	return NULL; // 데이터가 없으면 널값을 반환한다.

	//this->root.setCur(this->root.getHead()->getNext());

	//while (this->root.getCur() != this->root.getTail())
	//{ //노드를 타야지 링크드리스트를 타면 안된다. down이 NULL일 때까지.
	//	temp = compareListData(this->root.getCur()->getData(), item, check);
	//	if (check == true)
	//	{
	//		return temp;
	//	}
	//	else
	//	{
	//		// 아래로 내려가야 한다.
	//		this->root.setCur(this->root.getCur()->getNext());
	//	}
	//}
	//// 데이터가 없다면 널값을 반환한다.
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
//	return lp.getTail()->getPrev();// item이 모든 노드보다 클 시 마지막 노드의 주소를 리턴.
//}

int SkipList::dataInsert(int &item)
{
	if (this->dataSearch(item) != NULL)
	{
		return 0;
	}

	//if (this->root.getTail()->getPrev()->getData().linearSearchUnique(item) != NULL)
	//{ // 이것을 서치 로직으로 바꾼다.
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
	{ //위 아래 노드도 연결시켜야 되고 두 노드 중 크기가 큰 것을 위에 두어야 한다.(굳이 그럴 필요는 없지만 일단은.)
		LinkedList<int> obj;
		Node<int> *temp;
		 // 템프 지워야.
		temp = obj.appendFromTail(
			this->root.getHead()->getNext()->getData().getHead()->getNext()->getData());
		cout << "data : " << temp->getData() << endl;

		obj.appendFromTail(item); // 일단 여기에 원래의 데이터를 저장한다.
		// 저장하고 비교해서 가장 위에 무엇이 있어야 할지를 정한다.
		if (this->root.getTail()->getPrev()->getData().getTail()->getPrev()->getData() < item)
		{ // 처음 리스트의 첫 노드의 데이터가 아이템보다 작다면
			//cout << "original data : " << this->root.getHead()->getNext()->getData().getHead()->getNext()->getData() << endl;

			this->root.getHead()->getNext()->getData().getHead()->getNext()->setData(item);

			//this->root.getTail()->getData().getTail()->getPrev()->setData(item);
			//cout << "data2 : " << this->root.getHead()->getNext()->getData().getHead()->getNext()->getData() << endl;
		} // 그 데이터의 아이템을 아이템으로 세팅한다. 
		this->root.appendFromTail(obj);

		this->root.getTail()->getData().linkNode(
			this->root.getHead()->getNext()->getData().getHead()->getNext(), // 첫 리스트의 첫노드.
			this->root.getTail()->getPrev()->getData().linearSearchUnique(
			this->root.getHead()->getNext()->getData().getHead()->getNext()->getData()));
		// 둘째 리스트에서 첫째 데이터와 같은것과 연결한다.
		// 첫째 노드와 둘째 노드를 연결한다. ( 위와 아래를 연결한다. )
		this->level++;
		this->nodeNum += 2;
		return 1;
	}
	else if (this->root.getTail()->getPrev()->getData().getLength() + 1 <= 
		pow((double)2, this->level - 1))
	{ // 아이템보다 작은 위치를 찾아서 그곳에 아이템을 집어 넣는다.

		/*LinkedList<int> obj;
		int temp = pow(2, this->level - 1);
		cout << "temp : " << temp << endl;*/
		// 아이템을 집어넣고 노드를 연결시켜야 한다...
		//////
		// 여기서 링크노드는 필요없다. 아래로 내려가는 게 아니기 때문에.
		
		this->insertNewData(this->root.getTail()->getPrev()->getData(), item);
		// 맨 뒤 리스트에 그냥 노드 하나를 넣는다.

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
		////노드 비교 함수.

		//this->root.getTail()->getPrev()->getData().appendFromTail(item); // 아이템이 제일 크다면 끝에 넣는다.
		//////
		this->nodeNum++;

		return 1;
	}
	else
	{ // 새로 만들어서 새로운 레벨에 넣는다. 무엇을 연결할 지도 정한다.-> 위에 있는 것들은 모두 연결한다.
		LinkedList<int> obj;
		//가장 마지막 리스트의 cur을 조정.
		this->root.getTail()->getPrev()->getData().setCur(
			this->root.getTail()->getPrev()->getData().getHead()->getNext());

		while (this->root.getTail()->getPrev()->getData().getCur() != 
			this->root.getTail()->getPrev()->getData().getTail())
		{// 링크노드를 분명히 한다...
			Node<int> *temp;
			//링크노드와 어펜드를 나누고, 나중에 합친다.
			temp = obj.appendFromTail(this->root.getTail()->getPrev()->getData().getCur()->getData());
			// obj에 데이터를 추가한다. 그리고 노드와 연결 // 앞에것이 위에 있어야 한다.
			obj.linkNode(this->root.getTail()->getPrev()->getData().getCur(), temp);

			cout << "temp의 up : " << temp->getUp() << endl;
			cout << "root의 down : " << this->root.getTail()->getPrev()->getData().getCur()->getDown() << endl;

			//obj.linkNode(obj.appendFromTail(
			//	this->root.getTail()->getPrev()->getData().getCur()->getData()),
			//	this->root.getTail()->getPrev()->getData().getCur()); // 위에 있는 모든 데이터를 넣는다. 그리고
			//// 새로 넣은 노드와 위의 노드를 연결시킨다.

			this->root.getTail()->getPrev()->getData().setCur(
				this->root.getTail()->getPrev()->getData().getCur()->getNext()); // 다음으로 이동한다.
		} // while : tail 리스트의 모든 노드를 복사한다.
		//새로운 노드를 추가하고, 같은 것은 모두 연결한다.
		// 새 데이터를 적절한 자리에 넣고 연결해야 한다.
		this->insertNewData(obj, item);
		this->root.appendFromTail(obj);
		//this->insertNewData(this->root.appendFromTail(obj)->getData(), item);
		// 함수안에 함수를 넣으면 줄은 짧아지지만 내가 그것을 했는지를 알기가 어렵다.
		//obj를 리스트에 넣어야 된다...

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