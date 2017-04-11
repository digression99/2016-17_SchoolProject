#include "GenericDoubleLinkedList.h"

void create(LinkedList *lp)
{
	Node *head;
	Node *tail;

	head = (Node *)calloc(1, sizeof(Node)); // head와 tail에 Node 하나를 동적할당
	assert(head != NULL);
	tail = (Node *)calloc(1, sizeof(Node));
	assert(tail != NULL);

	lp->head = head; //list의 head와 tail이 각각 head node, tail node를 가리키게.
	lp->tail = tail;

	lp->head->prev = head; // head의 앞과 tail의 뒤는 없으므로
	lp->tail->next = tail; // 각각 자기 자신을 가리키게

	lp->head->next = tail; // head node와 tail node가 서로를 가리키게
	lp->tail->prev = head;

	lp->length = 0;

	return;
}

Node *appendFromHead(LinkedList *lp, void *item, size_t size, void(*myMemCpy)(void *, void *))
{
	lp->cur = (Node *)calloc(1, sizeof(Node)+size);
	assert(lp->cur != NULL);

	lp->cur->prev = lp->head; // New의 prev와 next의 포인터가 일단
	lp->cur->next = lp->head->next; // head와 head->next 사이에 끼어듬
	lp->head->next->prev = lp->cur; // head와 head->next가 각각
	lp->head->next = lp->cur; // New를 가리키게끔 포인터 정리

	myMemCpy((char *)lp->cur + sizeof(Node), item); // item을 복사

	lp->length++; // length 증가

	return lp->cur; // 새 노드의 주소를 리턴
}

Node *appendFromTail(LinkedList *lp, void *item, size_t size, void(*myMemCpy)(void *, void*))
{
	lp->cur = (Node *)calloc(sizeof(Node)+size, sizeof(char));
	assert(lp->cur != NULL);

	lp->cur->next = lp->tail; // New의 prev와 next의 포인터가 일단
	lp->cur->prev = lp->tail->prev;// tail과 tail->prev사이에 끼어듬

	lp->tail->prev->next = lp->cur; // tail과 tail->prev가 각각
	lp->tail->prev = lp->cur; // New를 가리키게끔 포인터 정리

	myMemCpy((char *)lp->cur + sizeof(Node), item);

	lp->length++; // length 증가

	return lp->cur; // 새 노드의 주소를 리턴
}

void display(LinkedList *lp, void(*dataPrint)(void *))
{ //리스트 내의 모든 데이터 노드 출력
	lp->cur = lp->head->next; // head의 다음 노드를 가리키게 함

	while (lp->cur != lp->tail)
	{
		dataPrint(lp->cur + 1);
		lp->cur = lp->cur->next; // 데이터를 출력 후
	} //                            그 다음 노드로 옮겨감

	return;
}

Node *insertBefore(LinkedList *lp, Node *index, void *item, size_t size, void(*myMemCpy)(void *, void *))
{
	lp->cur = (Node *)calloc(1, sizeof(Node)+size);
	assert(lp->cur != NULL);

	lp->cur->next = index; // 추가된 노드가 index의 앞뒤를 가리키게 포인터 정리
	lp->cur->prev = index->prev;

	index->prev->next = lp->cur;
	index->prev = lp->cur; // index의 앞뒤가 추가된 노드를 가리키게 포인터 정리

	myMemCpy(lp->cur + 1, item);
	//lp->cur->data = *dp; // 추가할 자료를 넣음

	lp->length++;

	return lp->cur; // 추가된 자료의 주소 리턴
}

Node *insertAfter(LinkedList *lp, Node *index, void *item, size_t size, void(*myMemCpy)(void *, void *))
{
	lp->cur = (Node *)calloc(1, sizeof(Node)+size);
	assert(lp->cur != NULL);

	lp->cur->next = index->next; //추가한 새 노드가 index의 앞뒤를 가리키게 포인터 정리
	lp->cur->prev = index;

	index->next->prev = lp->cur;
	index->next = lp->cur; // index의 앞뒤가 새 노드를 가리키게 포인터 정리

	myMemCpy(lp->cur + 1, item);
	//lp->cur->data = *dp;

	lp->length++;

	return lp->cur;
}

Node *deleteNode(LinkedList *lp, Node *index, void(*dataFree)(void *))
{
	dataFree(index + 1);
	lp->cur = index; // 삭제할 index의 위치를 lp->cur에 저장함

	index->next->prev = index->prev; // index의 앞뒤 노드가
	index->prev->next = index->next; // 서로를 가리키게 포인터 정리

	free(index); // index를 free함

	lp->length--;

	return lp->cur; //free한 index의 주소를 리턴
}

Node *linearsearchUnique(LinkedList *lp, void *target, int(*compare)(void *, void *))
{
	lp->cur = lp->head->next; // cur를 첫번째 노드를 가리키게

	while (lp->cur != lp->tail)
	{ // tail 전 노드까지 검색하게
		if (compare(target, lp->cur + 1) == 0)
		{ // target의 내용과 lp->cur +1의 내용이 일치하면
			return lp->cur; // 그 주소를 리턴
		}
		lp->cur = lp->cur->next; // 다음 노드로 옮겨감
	}

	return NULL;
}

void sortList(LinkedList *lp, size_t size, int(*compare)(void *, void *), void(*myMemCpy)(void *, void *))
{
	Node *savep; // 비교할 노드의 주소를 저장할 포인터 선언
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
			{ //cur의 name과 savep의 name을 비교하여 savep의 name이

				myMemCpy(temp, savep + 1);
				myMemCpy(savep + 1, lp->cur + 1);
				myMemCpy(lp->cur + 1, temp);
			}
			lp->cur = lp->cur->next; // cur를 그 다음 노드로 옮겨가게
		}
		savep = savep->next; // savep를 그 다음 노드로 옮겨가게
		lp->cur = savep->next; // cur는 savep의 다음 노드를 가리키게
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
{ // lp1을 완전히 없앤 후에 다시 창조한다.
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