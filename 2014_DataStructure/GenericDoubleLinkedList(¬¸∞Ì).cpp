#include "GenericDoubleLinkedList.h"

void create(LinkedList *lp)
{
	Node *head;
	Node *tail;

	head = (Node *)calloc(1, sizeof(Node)); // head�� tail�� Node �ϳ��� �����Ҵ�
	assert(head != NULL);
	tail = (Node *)calloc(1, sizeof(Node));
	assert(tail != NULL);

	lp->head = head; //list�� head�� tail�� ���� head node, tail node�� ����Ű��.
	lp->tail = tail;

	lp->head->prev = head; // head�� �հ� tail�� �ڴ� �����Ƿ�
	lp->tail->next = tail; // ���� �ڱ� �ڽ��� ����Ű��

	lp->head->next = tail; // head node�� tail node�� ���θ� ����Ű��
	lp->tail->prev = head;

	lp->length = 0;

	return;
}

Node *appendFromHead(LinkedList *lp, void *item, size_t size, void(*myMemCpy)(void *, void *))
{
	lp->cur = (Node *)calloc(1, sizeof(Node)+size);
	assert(lp->cur != NULL);

	lp->cur->prev = lp->head; // New�� prev�� next�� �����Ͱ� �ϴ�
	lp->cur->next = lp->head->next; // head�� head->next ���̿� �����
	lp->head->next->prev = lp->cur; // head�� head->next�� ����
	lp->head->next = lp->cur; // New�� ����Ű�Բ� ������ ����

	myMemCpy((char *)lp->cur + sizeof(Node), item); // item�� ����

	lp->length++; // length ����

	return lp->cur; // �� ����� �ּҸ� ����
}

Node *appendFromTail(LinkedList *lp, void *item, size_t size, void(*myMemCpy)(void *, void*))
{
	lp->cur = (Node *)calloc(sizeof(Node)+size, sizeof(char));
	assert(lp->cur != NULL);

	lp->cur->next = lp->tail; // New�� prev�� next�� �����Ͱ� �ϴ�
	lp->cur->prev = lp->tail->prev;// tail�� tail->prev���̿� �����

	lp->tail->prev->next = lp->cur; // tail�� tail->prev�� ����
	lp->tail->prev = lp->cur; // New�� ����Ű�Բ� ������ ����

	myMemCpy((char *)lp->cur + sizeof(Node), item);

	lp->length++; // length ����

	return lp->cur; // �� ����� �ּҸ� ����
}

void display(LinkedList *lp, void(*dataPrint)(void *))
{ //����Ʈ ���� ��� ������ ��� ���
	lp->cur = lp->head->next; // head�� ���� ��带 ����Ű�� ��

	while (lp->cur != lp->tail)
	{
		dataPrint(lp->cur + 1);
		lp->cur = lp->cur->next; // �����͸� ��� ��
	} //                            �� ���� ���� �Űܰ�

	return;
}

Node *insertBefore(LinkedList *lp, Node *index, void *item, size_t size, void(*myMemCpy)(void *, void *))
{
	lp->cur = (Node *)calloc(1, sizeof(Node)+size);
	assert(lp->cur != NULL);

	lp->cur->next = index; // �߰��� ��尡 index�� �յڸ� ����Ű�� ������ ����
	lp->cur->prev = index->prev;

	index->prev->next = lp->cur;
	index->prev = lp->cur; // index�� �յڰ� �߰��� ��带 ����Ű�� ������ ����

	myMemCpy(lp->cur + 1, item);
	//lp->cur->data = *dp; // �߰��� �ڷḦ ����

	lp->length++;

	return lp->cur; // �߰��� �ڷ��� �ּ� ����
}

Node *insertAfter(LinkedList *lp, Node *index, void *item, size_t size, void(*myMemCpy)(void *, void *))
{
	lp->cur = (Node *)calloc(1, sizeof(Node)+size);
	assert(lp->cur != NULL);

	lp->cur->next = index->next; //�߰��� �� ��尡 index�� �յڸ� ����Ű�� ������ ����
	lp->cur->prev = index;

	index->next->prev = lp->cur;
	index->next = lp->cur; // index�� �յڰ� �� ��带 ����Ű�� ������ ����

	myMemCpy(lp->cur + 1, item);
	//lp->cur->data = *dp;

	lp->length++;

	return lp->cur;
}

Node *deleteNode(LinkedList *lp, Node *index, void(*dataFree)(void *))
{
	dataFree(index + 1);
	lp->cur = index; // ������ index�� ��ġ�� lp->cur�� ������

	index->next->prev = index->prev; // index�� �յ� ��尡
	index->prev->next = index->next; // ���θ� ����Ű�� ������ ����

	free(index); // index�� free��

	lp->length--;

	return lp->cur; //free�� index�� �ּҸ� ����
}

Node *linearsearchUnique(LinkedList *lp, void *target, int(*compare)(void *, void *))
{
	lp->cur = lp->head->next; // cur�� ù��° ��带 ����Ű��

	while (lp->cur != lp->tail)
	{ // tail �� ������ �˻��ϰ�
		if (compare(target, lp->cur + 1) == 0)
		{ // target�� ����� lp->cur +1�� ������ ��ġ�ϸ�
			return lp->cur; // �� �ּҸ� ����
		}
		lp->cur = lp->cur->next; // ���� ���� �Űܰ�
	}

	return NULL;
}

void sortList(LinkedList *lp, size_t size, int(*compare)(void *, void *), void(*myMemCpy)(void *, void *))
{
	Node *savep; // ���� ����� �ּҸ� ������ ������ ����
	void *temp;

	temp = (char *)calloc(size, sizeof(char));
	assert(temp != NULL);

	savep = lp->head->next;
	lp->cur = savep->next;

	while (savep != lp->tail->prev)
	{
		while (lp->cur != lp->tail)
		{
			if (compare(savep + 1, lp->cur + 1) > 0)
			{ //cur�� name�� savep�� name�� ���Ͽ� savep�� name��

				myMemCpy(temp, savep + 1);
				myMemCpy(savep + 1, lp->cur + 1);
				myMemCpy(lp->cur + 1, temp);
			}
			lp->cur = lp->cur->next; // cur�� �� ���� ���� �Űܰ���
		}
		savep = savep->next; // savep�� �� ���� ���� �Űܰ���
		lp->cur = savep->next; // cur�� savep�� ���� ��带 ����Ű��
	}
	free(temp);

	return;
}

void destroy(LinkedList *lp, void(*dataFree)(void *))
{
	Node *tp;
	lp->cur = lp->head->next;
	tp = lp->cur;

	while (lp->cur != lp->tail)
	{
		lp->cur->next->prev = lp->cur->prev;
		lp->cur->prev->next = lp->cur->next;
		lp->length--;
		dataFree(lp->cur + 1);
		lp->cur = lp->cur->next;
		free(tp);
		tp = lp->cur;
	}

	free(lp->head);
	free(lp->tail);

	return;
}

void getAt(Node *index, void *getData, void(*myMemCpy)(void *, void *))
{
	myMemCpy(getData, index + 1);

	return;
}

void saveListData(LinkedList *lp, FILE *fp, void(*saveData)(FILE *,void *))
{
	lp->cur = lp->head->next;

	while (lp->cur != lp->tail)
	{
		saveData(fp, lp->cur + 1);
		lp->cur = lp->cur->next;
	}

	return;
}

void listMemCpy(LinkedList *lp1, LinkedList *lp2, size_t size,
		void(*myMemCpy)(void *, void *), void(*myFree)(void *))
{ // lp1�� ������ ���� �Ŀ� �ٽ� â���Ѵ�.
	if (lp1->length != 0)
	{
		destroy(lp1, myFree);
	}
	create(lp1);

	//lp1->cur = lp1->head->next;
	lp2->cur = lp2->head->next;

	while (lp2->cur != lp2->tail)
	{
		appendFromHead(lp1, lp2->cur + 1, size, myMemCpy);
		lp2->cur = lp2->cur->next;
	}

	return;
}