/*
20166282 ��ǻ�Ͱ��а� 4�г� ���¼�
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
	//lprint()�� l�� ����Ű�� �������� ��ũ�� ���󰡸� ������ ���
	//rprint()�� r�� ����Ű�� �������� ��ũ�� ���󰡸� ������ ���

	printf("�ʱ��� ����\n");
	create();	//��� ���� 10 <- 20 <- 30(l) 40(r) -> 50 -> 60
	lPrint();
	rPrint();
	printf("\n");
	nright(1);	//���������� �� ��� �̵�
	lPrint();
	rPrint();
	printf("\n");
	nleft(3);	//�������� �� ��� �̵�
	lPrint();
	rPrint();
	printf("\n");
	nright(5);	//���������� �ټ� ��� �̵�
	lPrint();
	rPrint();
	printf("\n");
	nleft(7);	//�������� �ϰ� ��� �̵�
	lPrint();
	rPrint();

}


//��� ���� �Լ�
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


//���������� n��常ŭ �����͸� �̵��ϴ� �Լ� 
void nright(int n) {
	
	printf("���������� %d��常ŭ l,r�����͸� �̵��մϴ�.", n);
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
			printf("left�� ������ ��忡 �����߽��ϴ�. �� �̻� ������ �� �����ϴ�.");
	}


}


//�������� n��常ŭ �����͸� �̵��ϴ� �Լ�
void nleft(int n) {
	
	printf("�������� %d��常ŭ l,r�����͸� �̵��մϴ�.", n);
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
			printf("right�� ó�� ��忡 �����߽��ϴ�.�� �̻� �̵��� �� �����ϴ�.\n");
	}
}


//r�� ����Ű�� �������� ��ũ�� ���󰡸� ������ ���
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


//l�� ����Ű�� �������� ��ũ�� ���󰡸� ������ ���
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


