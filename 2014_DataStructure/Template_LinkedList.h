#pragma once

#include <iostream>
using namespace std;

template <typename T>
class Node
{ // 일단 public으로 하고 Connect, Disconnect함수를 제작하는 것을 목표로.
public: // 노드에 데이터도 넣을까? 그러려면 템플릿으로 해야. 그럴 수 없다.
	Node<T> *prev;
	T data;
	Node<T> *next;
	Node<T> *up;
	Node<T> *down;
	Node();
	~Node() {};
	T &getData();
	Node<T> *getUp();
	Node<T> *getDown();
	Node<T> *getPrev();
	Node<T> *getNext();
	void setUp(Node<T> *index);
	void setDown(Node<T> *index);
	void setPrev(Node<T> *index);
	void setNext(Node<T> *index);
	void setData(T &data);

	friend void nodeDataMemCpy(T *a, T &b);
};

template <typename T>
Node<T>::Node()
{
	this->prev = NULL;
	this->next = NULL;
	this->up = NULL;
	this->down = NULL;
	//this->data = 0;
}


template <typename T>
void Node<T>::setNext(Node<T> *index)
{
	this->next = index;
}

template <typename T>
void Node<T>::setPrev(Node<T> *index)
{
	this->prev = index;
}

template <typename T>
void Node<T>::setData(T &data)
{
	nodeDataMemCpy(&this->data, data);
}

void nodeDataMemCpy(int *item1, int &item2)
{
	*item1 = item2;
}

template <typename T>
void Node<T>::setUp(Node<T> *index)
{
	this->up = index;
}

template <typename T>
void Node<T>::setDown(Node<T> *index)
{
	this->down = index;
}

template <typename T>
Node<T> *Node<T>::getUp()
{
	return this->up;
}

template <typename T>
Node<T> *Node<T>::getDown()
{
	return this->down;
}

template <typename T>
Node<T> *Node<T>::getPrev()
{
	return this->prev;
}

template <typename T>
Node<T> *Node<T>::getNext()
{
	return this->next;
}

template <typename T>
T &Node<T>::getData()
{
	return this->data;
}

template <typename T>
class LinkedList
{
private:
	Node<T> *head;
	Node<T> *tail;
	Node<T> *cur;
	int length;
public:
	LinkedList();
	~LinkedList();
	LinkedList(const LinkedList<T> &);
	int compareNodeData(T &, T &);
	Node<T> *appendFromHead(T &item); // appendFromHead자체를 friend로 선언?
	Node<T> *appendFromTail(T &item);
	Node<T> *insertAfter(Node<T> *index, T &item);
	Node<T> *insertBefore(Node<T> *index, T &item);
	Node<T> *linearSearchUnique(T &target);
	Node<T> *deleteNode(Node<T> *index);
	Node<T> *linkNode(Node<T> *index, Node<T> *index2);
	Node<T> *unlinkNode(Node<T> *index, Node<T> *index2); // 언링크와 딜리트를 같이 해야될 듯.->재귀
	void clearLinkedList(); // 두 노드를 주면 두 노드의 up, down 연결을 끊는다.
	int getLength(); // 윗노드의 주소를 리턴해야.
	Node<T> *getHead();
	Node<T> *getTail();
	Node<T> *getCur();
	void setCur(Node<T> *index);
	void setHead(Node<T> *index);
	void setTail(Node<T> *index);
	void setLength(int num);

	friend int dataAmountCompare(T &, T &);
	friend int dataCompare(T &, T &);
	friend void dataMemCpy(T &, T &);
	friend void dataDisplay(T &);
	friend void dataFree(T &);
	void display();
};

template <typename T>
int LinkedList<T>::compareNodeData(T &a, T &b)
{
	if (dataAmountCompare(a, b) == 0)
	{
		return 0;
	} // 앞의노드 데이터가 크면 0, 작으면 1
	return 1;
}

int dataAmountCompare(int &a, int &b)
{
	if (a > b)
	{ // 앞의 데이터가 크면 0, 작으면 1
		return 0;
	}
	return 1;
}

template <typename T>
Node<T> *LinkedList<T>::unlinkNode(Node<T> *index, Node<T> *index2)
{ // 재귀는 skiplist에서 하자.
	index->setDown(NULL);
	index2->setUp(NULL);
	
	return index;
}

template <typename T>
void LinkedList<T>::setLength(int num)
{
	this->length = num;
}

template <typename T>
void LinkedList<T>::setHead(Node<T> *index)
{
	this->head = index;
}

template <typename T>
void LinkedList<T>::setTail(Node<T> *index)
{
	this->tail = index;
}

template <typename T>
Node<T> *LinkedList<T>::linkNode(Node<T> *index, Node<T> *index2)
{ // 두 노드를 위 아래로 연결한다. index가 위, index2가 아래에 위치.
	index->setDown(index2);
	index2->setUp(index);

	return index; // 연결한 노드를 리턴한다. (위에 있는 것)
}

template <typename T>
Node<T> *LinkedList<T>::appendFromTail(T &item)
{
	this->cur = new Node<T>;
	dataMemCpy(this->cur->data, item);

	this->cur->next = this->tail;
	this->cur->prev = this->tail->prev;

	this->tail->prev->next = this->cur;
	this->tail->prev = this->cur;

	this->length++;

	return this->cur;
}

template <typename T>
void LinkedList<T>::setCur(Node<T> *index)
{
	this->cur = index;
}

template <typename T>
Node<T> *LinkedList<T>::getHead()
{
	return this->head;
}

template <typename T>
Node<T> *LinkedList<T>::getTail()
{
	return this->tail;
}

template <typename T>
Node<T> *LinkedList<T>::getCur()
{
	return this->cur;
}


template <typename T>
void LinkedList<T>::clearLinkedList()
{
	if (this->length == 0)
	{
		return;
	}
	this->cur = this->head->next;

	while (this->cur != this->tail)
	{
		deleteNode(this->cur);
		this->cur = this->cur->next;
	}
}

template <typename T>
int LinkedList<T>::getLength()
{
	return this->length;
}

template <typename T>
Node<T> *LinkedList<T>::linearSearchUnique(T &target)
{
	this->cur = this->head->next;

	while (this->cur != this->tail)
	{
		if (dataCompare(this->cur->data, target) == 0)
		{
			return this->cur;
		}
		this->cur = this->cur->next;
	}
	return NULL;
}

template <typename T>
Node<T> *LinkedList<T>::insertBefore(Node<T> *index, T&item)
{
	this->cur = new Node<T>;
	dataMemCpy(this->cur->data, item);

	this->cur->setNext(index);
	this->cur->setPrev(index->getPrev());

	index->getPrev()->setNext(this->cur);
	index->setPrev(this->cur);

	this->length++;

	return this->cur;
}

template <typename T>
Node<T> *LinkedList<T>::insertAfter(Node <T> *index, T &item)
{
	this->cur = new Node<T>;
	dataMemCpy(this->cur->data, item);

	this->cur->next = index->next;
	this->cur->prev = index;

	index->next->prev = this->cur;
	index->next = this->cur;

	this->length++;

	return this->cur;
}

template <typename T>
Node<T> *LinkedList<T>::deleteNode(Node<T> *index)
{
	this->cur = index;

	this->cur->next->prev = this->cur->prev;
	this->cur->prev->next = this->cur->next;

	dataFree(this->cur->data);
	delete this->cur;
	this->length--;

	return this->cur;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	this->cur = this->head->next;

	while (this->cur != this->tail)
	{
		dataFree(this->cur->data);
		this->cur = this->cur->next;
	}
}

template <typename T>
void LinkedList<T>::display()
{
	this->cur = this->head->next;

	while (this->cur != this->tail)
	{
		dataDisplay(this->cur->data);
		this->cur = this->cur->getNext();
	}
}

template <typename T>
LinkedList<T>::LinkedList()
{
	this->head = new Node<T>;
	this->tail = new Node<T>;
	this->head->next = this->tail;
	this->tail->prev = this->head;
	this->head->prev = this->head;
	this->tail->next = this->tail;

	this->length = 0;
}

template <typename T>
Node<T> *LinkedList<T>::appendFromHead(T &item)
{
	this->cur = new Node<T>;
	dataMemCpy(this->cur->data, item);

	this->cur->prev = this->head;
	this->cur->next = this->head->next;

	this->head->next->prev = this->cur;
	this->head->next = this->cur;

	this->length++;

	return this->cur;
}

void dataMemCpy(double &a, double &b)
{
	a = b;
}

void dataMemCpy(int &a, int &b)
{
	a = b;
}

void dataMemCpy(LinkedList<int> &a, LinkedList<int> &b)
{
	if (a.getLength() != 0)
	{
		a.clearLinkedList();
	}
	a.setCur(a.getHead()->getNext());
	b.setCur(b.getHead()->getNext());

	while (b.getCur() != b.getTail())
	{
		a.appendFromTail(b.getCur()->getData());
		b.setCur(b.getCur()->getNext());
	}
}

void dataDisplay(int &a)
{
	cout << "int data : " << a << endl;
}

void dataDisplay(double &a)
{
	cout << "double data : " << a << endl;
}

void dataDisplay(LinkedList<int> &a)
{
	a.display();
}

void dataFree(int &a)
{
	cout << "Freed int data" << endl;
}

void dataFree(double &a)
{
	cout << "Freed double data" << endl;
}

void dataFree(LinkedList<int> &dp)
{
	dp.setCur(dp.getHead()->getNext());

	while (dp.getCur() != dp.getTail())
	{
		dataFree(dp.getCur()->getData());
		dp.setCur(dp.getCur()->getNext());
	}
}

int dataCompare(LinkedList<int> &a, LinkedList<int> &b)
{ // 두 링크드리스트를 비교.
	a.setCur(a.getHead()->getNext());
	b.setCur(b.getHead()->getNext());

	while (a.getCur() != a.getTail())
	{
		if (a.getCur()->getData() != b.getCur()->getData())
		{
			return 1;
		}
		a.setCur(a.getCur()->getNext());
		b.setCur(b.getCur()->getNext());
	}
	return 0;
}

int dataCompare(int &a, int &b)
{
	if (a == b)
	{
		return 0;
	}
	return 1;
}

int dataCompare(double &a, double &b)
{
	if (a == b)
	{
		return 0;
	}
	return 1;
}