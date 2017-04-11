#pragma once
#pragma warning(disable : 4996)

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <process.h>
#include <Windows.h>
#include <conio.h>

#define CLEAR system("cls")
#define WAITINGTIME 500
#define WAIT Sleep(WAITINGTIME)

typedef struct _node Node;

struct _node
{
	Node *prev;
	Node *next;
};

typedef struct _linkedList
{
	Node *head;
	Node *tail;
	Node *cur;
	int length;
} LinkedList;

void create(LinkedList *);
Node *appendFromHead(LinkedList *lp, void *item, size_t size, void(*myMemCpy)(void *, void *));
Node *appendFromTail(LinkedList *lp, void *item, size_t size, void(*myMemCpy)(void *, void*));
void display(LinkedList *lp, void(*dataPrint)(void *));
Node *insertBefore(LinkedList *lp, Node *index, void *item, size_t size, void(*myMemCpy)(void *, void *));
Node *insertAfter(LinkedList *, Node *, void *item, size_t size, void(*myMemCpy)(void *, void *));
Node *deleteNode(LinkedList *lp, Node *index, void(*dataFree)(void *));
Node *linearsearchUnique(LinkedList *lp, void *target, int(*compare)(void *, void *));
void destroy(LinkedList *lp, void(*dataFree)(void *));
void getAt(Node *index, void *getData, void(*myMemCpy)(void *, void *));
void sortList(LinkedList *lp, size_t size, int(*compare)(void *, void *), void(*myMemCpy)(void *, void *));
void saveListData(LinkedList *lp, FILE *fp, void(*saveData)(FILE *, void *));
void listMemCpy(LinkedList *lp1, LinkedList *lp2, size_t size, void(*myMemCpy)(void *, void *), void(*myFree)(void *));