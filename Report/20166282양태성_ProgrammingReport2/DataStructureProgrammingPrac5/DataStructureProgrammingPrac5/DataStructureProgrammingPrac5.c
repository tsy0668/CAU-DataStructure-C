/*
중앙대학교 컴퓨터공학과 4학년 20166282 양태성 
Data Structure - Programming Report
Making Loser Tree
*/

#include <stdio.h>
#include <stdlib.h>


#define numRow 8
#define numCol 10


typedef struct node* treePointer;
typedef struct node {
	int rownum;		//최종승자 출력시 Row Number를 출력하기 위한 변수
	int data;		//노드의 value
	int count;		//중복노드의 개수
	treePointer leftChild, rightChild;
} node;


int matrix[numRow][numCol] = {
{ 5,90,5,9,80,80,7,90,7,90 },
{ 100,30,30,51,160,160,160,51,160,59 },
{ 500,100,7000,100,900,600,100,100,650,100 },
{ 1000,300,41,300,41,41,41,900,900,950 },
{ 90,81,81,95,81,83,81,90,81,90 },
{ 30,30,40,40,50,50,50,120,140,140},
{ 1,1,5,5,5,5,5,5,7,7},
{ 3000,3000,4000,4000,4500,6000,6000,6000,6000,200}
};


treePointer wholeTree[numRow] = { NULL };			//연결리스트로 구현된 이진탐색트리 배열
treePointer loserTree[numRow * 2 - 1] = { NULL };	//패자트리(패자트리의 노드 수는 numRow * 2 - 1개)
treePointer winner[numRow * 2 - 1] = { NULL };		//패자트리의 토너먼트에서 임의로 저장 될 승자
treePointer tmp;									//연결리스트의 연결을 위한 임시 노드
int maxcount = 0;	//패자트리의 단말로 가기 위하여 이진탐색트리의 max count를 기록하는 변수
int presentNum = 0;	//이진탐색트리 생성 중에 row의 번호를 기억하여 노드의 rownum를 기록하기 위한 변수
int nodecount = 0;	//node수 만큼 패자트리의 생성횟수(토너먼트 반복횟수)를 정하는 변수



void createBin(treePointer* node, int k);				//이진트리 생성함수
treePointer modifiedSearch(treePointer tree, int k);	//노드의 중복검사 함수
void treePrint(treePointer tree);						//생성된 이진탐색트리를 출력
void createLoser(treePointer tree);						//패자트리 구현 후 출력
void traverse(treePointer tree);						//패자트리의 최종승자 결정 후 다음 패자트리의 단말노드에 들어올 노드 탐색
void deleteNode(treePointer tree, int k);				//최종승자로 선정된 노드를 삭제
void recreateLoser(treePointer* tree);					//패자 토너먼트 반복하여 최종승자 출력


void main() {

	int i, j;

	for (i = 0; i < numRow; i++) {
		
		presentNum = i;
		
		for (j = 0; j < numCol; j++) {
			
			createBin(&wholeTree[i], matrix[i][j]);
		
		}
		
		printf("=================wholeTree[%d]===============\n", i);
		treePrint(wholeTree[i]);
		printf("\n\n");

	}

	createLoser(&wholeTree);
	recreateLoser(&wholeTree);

}


void createBin(treePointer* node, int k) {

	treePointer ptr, temp = modifiedSearch(*node, k);
	
	if (temp || !(*node)) {
		
		ptr = (treePointer)malloc(sizeof(*ptr));
		ptr->rownum = presentNum;	//현재 행넘버를 rownum변수에 추가
		ptr->data = k;
		ptr->count = 1;			//노드 생성 시에 count 추가
		ptr->leftChild = ptr->rightChild = NULL;

		if (*node) {
			
			if (k < temp->data)
				temp->leftChild = ptr;
			else
				temp->rightChild = ptr;
		
		}
		
		else
			*node = ptr;
	}
}


treePointer modifiedSearch(treePointer tree, int k) {

	while (tree) {

		if (k == tree->data) {
			tree->count++;		//현재 추가하려는 데이터의 value가 이미 존재하면 count증가
			return NULL;
		}

		if (k < tree->data)
			if (tree->leftChild)
				tree = tree->leftChild;
			else
				break;
		else
			if (tree->rightChild)
				tree = tree->rightChild;
			else
				break;
	
	}

	return tree;

}


void treePrint(treePointer tree) {
	
	if (tree) {
		
		treePrint(tree->leftChild);
		printf("row[%d]  data : %d   count : %d \n", tree->rownum,tree->data,tree->count);
		treePrint(tree->rightChild);
	
	}

}


void createLoser(treePointer *tree) {
	
		int n = 0;
		int m = 0;

		for (n = numRow * 2 - 2; n >= numRow - 1; n--) {

			maxcount = 0;
			presentNum = n - numRow + 1;

			traverse(tree[n - numRow + 1]);

			loserTree[n] = tmp;
			winner[n] = tmp;
		
		}

		for (m = 2; m < numRow * 2; m += 2) {

			if (winner[numRow * 2 - m]->count > winner[numRow * 2 - m - 1]->count) {

				loserTree[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m - 1];
				winner[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m];

			}

			else if (winner[numRow * 2 - m]->count == winner[numRow * 2 - m - 1]->count) {

				if (winner[numRow * 2 - m]->data > winner[numRow * 2 - m - 1]->data) {

					loserTree[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m - 1];
					winner[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m];

				}

				else if (winner[numRow * 2 - m]->data == winner[numRow * 2 - m - 1]->data) {

					if (winner[numRow * 2 - m]->rownum > winner[numRow * 2 - m - 1]->rownum) {

						loserTree[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m - 1];
						winner[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m];

					}

					else {

						loserTree[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m];
						winner[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m - 1];

					}
				}
				else {

					loserTree[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m];
					winner[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m - 1];

				}
			}

			else {

				loserTree[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m];
				winner[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m - 1];

			}

		}

		printf("+++++++++++++++++++++LoserTree++++++++++++++++++++++++\n");
		
		for (m = 0; m <= numRow * 2 - 2; m++)
			printf("<loserTree[%d]>  count :  %d    data :  %d\n", m, loserTree[m]->count, loserTree[m]->data);

		nodecount = winner[0]->count;
		printf("\n<%d, %d, %d>\n", winner[0]->rownum, winner[0]->data, winner[0]->count);
	
}


void recreateLoser(treePointer* tree) {

	int m = 0;

	while(nodecount < numRow*numCol) {

		maxcount = 0;
		
		deleteNode(wholeTree[winner[0]->rownum], winner[0]->data);
		traverse(wholeTree[winner[0]->rownum]);

		loserTree[numRow - 1 + winner[0]->rownum] = tmp;
		winner[numRow - 1 + winner[0]->rownum] = tmp;
		
		for (m = 2; m < numRow * 2; m += 2) {

			if (winner[numRow * 2 - m]->count > winner[numRow * 2 - m - 1]->count) {

				loserTree[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m - 1];
				winner[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m];

			}

			else if (winner[numRow * 2 - m]->count == winner[numRow * 2 - m - 1]->count) {

				if (winner[numRow * 2 - m]->data > winner[numRow * 2 - m - 1]->data) {

					loserTree[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m - 1];
					winner[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m];

				}

				else if (winner[numRow * 2 - m]->data == winner[numRow * 2 - m - 1]->data) {

					if (winner[numRow * 2 - m]->rownum > winner[numRow * 2 - m - 1]->rownum) {

						loserTree[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m - 1];
						winner[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m];

					}

					else {

						loserTree[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m];
						winner[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m - 1];

					}
				}
				else {

					loserTree[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m];
					winner[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m - 1];

				}
			}

			else {

				loserTree[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m];
				winner[(numRow * 2 - m - 1) / 2] = winner[numRow * 2 - m - 1];

			}

		}

		nodecount += winner[0]->count;
		printf("<%d, %d, %d>\n", winner[0]->rownum, winner[0]->data, winner[0]->count);
		
	}
}


void traverse(treePointer tree) {

	if (tree != NULL) {
		
		traverse(tree->leftChild);
		
		if (tree->count > maxcount) {
			
			maxcount = tree->count;
			tmp = tree;
		
		}
		
		if (tree->count == maxcount)
			if (tree->data > tmp->data)
				tmp = tree;

		traverse(tree->rightChild);
	}

}

void deleteNode(treePointer tree, int k) {

	while (tree) {

		if (k == tree->data) {
			tree->count = -1;
		}

		if (k < tree->data)
			if (tree->leftChild)
				tree = tree->leftChild;
			else
				break;
		else
			if (tree->rightChild)
				tree = tree->rightChild;
			else
				break;
	}

}

