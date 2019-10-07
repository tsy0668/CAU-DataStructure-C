/*
20166282 컴퓨터공학과 4학년 양태성
DataStructure Report(Chapter4)
*/


#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
} listNode;


listPointer l, r;


void create();
void nright(int n);
void nleft(int n);
void rPrint();
void lPrint();


void main()
{
	//lprint()로 l이 가리키는 포인터의 링크를 따라가며 데이터 출력
	//rprint()로 r이 가리키는 포인터의 링크를 따라가며 데이터 출력

	printf("초기노드 생성\n");
	create();	//노드 생성 10 <- 20 <- 30(l) 40(r) -> 50 -> 60
	lPrint();
	rPrint();
	printf("\n");
	nright(1);	//오른쪽으로 한 노드 이동
	lPrint();
	rPrint();
	printf("\n");
	nleft(3);	//왼쪽으로 세 노드 이동
	lPrint();
	rPrint();
	printf("\n");
	nright(5);	//오른쪽으로 다섯 노드 이동
	lPrint();
	rPrint();
	printf("\n");
	nleft(7);	//왼쪽으로 일곱 노드 이동
	lPrint();
	rPrint();

}


//노드 생성 함수
void create() {
	listNode *first, *second, *third, *fourth, *fifth, *sixth;
	first = (listPointer)malloc(sizeof(listNode));
	second = (listPointer)malloc(sizeof(listNode));
	third = (listPointer)malloc(sizeof(listNode));
	fourth = (listPointer)malloc(sizeof(listNode));
	fifth = (listPointer)malloc(sizeof(listNode));
	sixth = (listPointer)malloc(sizeof(listNode));


	first->link = NULL;
	second->link = first;
	third->link = second;
	fourth->link = fifth;
	fifth->link = sixth;
	sixth->link = NULL;
	
	first->data = 10;
	second->data = 20;
	third->data = 30;
	fourth->data = 40;
	fifth->data = 50;
	sixth->data = 60;

	l = third;
	r = fourth;

}


//오른쪽으로 n노드만큼 포인터를 이동하는 함수 
void nright(int n) {
	
	printf("오른쪽으로 %d노드만큼 l,r포인터를 이동합니다.", n);
	printf("\n");
	int i;
	listPointer temp;

	for (i = 0; i < n; i++) {
		if (r) {
			temp = l;
			l = r;
			r = r->link;
			l->link = temp;
		}
		else
			printf("left가 마지막 노드에 도달했습니다. 더 이상 움직일 수 없습니다.");
	}


}


//왼쪽으로 n노드만큼 포인터를 이동하는 함수
void nleft(int n) {
	
	printf("왼쪽으로 %d노드만큼 l,r포인터를 이동합니다.", n);
	printf("\n");
	int i;
	listPointer temp;

	for (i = 0; i < n; i++) {
		if (l) {
			temp = r;
			r = l;
			l = l->link;
			r->link = temp;
		}
		else
			printf("right가 처음 노드에 도달했습니다.더 이상 이동할 수 없습니다.\n");
	}
}


//r이 가리키는 포인터의 링크를 따라가며 데이터 출력
void rPrint()
{
	listPointer temp = NULL;
	temp = r;
	printf("The Right List contains: ");

	for (; r; r = r->link) {
		printf("%d -> ", r->data);
	}

	if (r == NULL)
		printf("NULL");

	r = temp;
	printf("\n");
}


//l이 가리키는 포인터의 링크를 따라가며 데이터 출력
void lPrint()
{
	int lcount = 0;
	int lcount_temp = 0;
	int i;
	int ldata[6];
	listPointer temp = NULL;
	temp = l;

	printf("The Left List contains: ");

	for (; l; l = l->link)
		lcount++;

	l = temp;
	lcount_temp = lcount;

	for (; l; l = l->link)
		ldata[--lcount] = l->data;

	printf("NULL");
	for (i = 0; i < lcount_temp; i++) {
		printf("<- %d ", ldata[i]);
	}

	l = temp;
	printf("\n");
}


