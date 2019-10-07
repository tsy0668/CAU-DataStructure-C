/*
�߾Ӵ��б� ��ǻ�Ͱ��а� 4�г� 20166282 ���¼� 
Data Structure - Programming Report
Making Loser Tree
*/

#include <stdio.h>
#include <stdlib.h>


#define numRow 8
#define numCol 10


typedef struct node* treePointer;
typedef struct node {
	int rownum;		//�������� ��½� Row Number�� ����ϱ� ���� ����
	int data;		//����� value
	int count;		//�ߺ������ ����
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


treePointer wholeTree[numRow] = { NULL };			//���Ḯ��Ʈ�� ������ ����Ž��Ʈ�� �迭
treePointer loserTree[numRow * 2 - 1] = { NULL };	//����Ʈ��(����Ʈ���� ��� ���� numRow * 2 - 1��)
treePointer winner[numRow * 2 - 1] = { NULL };		//����Ʈ���� ��ʸ�Ʈ���� ���Ƿ� ���� �� ����
treePointer tmp;									//���Ḯ��Ʈ�� ������ ���� �ӽ� ���
int maxcount = 0;	//����Ʈ���� �ܸ��� ���� ���Ͽ� ����Ž��Ʈ���� max count�� ����ϴ� ����
int presentNum = 0;	//����Ž��Ʈ�� ���� �߿� row�� ��ȣ�� ����Ͽ� ����� rownum�� ����ϱ� ���� ����
int nodecount = 0;	//node�� ��ŭ ����Ʈ���� ����Ƚ��(��ʸ�Ʈ �ݺ�Ƚ��)�� ���ϴ� ����



void createBin(treePointer* node, int k);				//����Ʈ�� �����Լ�
treePointer modifiedSearch(treePointer tree, int k);	//����� �ߺ��˻� �Լ�
void treePrint(treePointer tree);						//������ ����Ž��Ʈ���� ���
void createLoser(treePointer tree);						//����Ʈ�� ���� �� ���
void traverse(treePointer tree);						//����Ʈ���� �������� ���� �� ���� ����Ʈ���� �ܸ���忡 ���� ��� Ž��
void deleteNode(treePointer tree, int k);				//�������ڷ� ������ ��带 ����
void recreateLoser(treePointer* tree);					//���� ��ʸ�Ʈ �ݺ��Ͽ� �������� ���


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
		ptr->rownum = presentNum;	//���� ��ѹ��� rownum������ �߰�
		ptr->data = k;
		ptr->count = 1;			//��� ���� �ÿ� count �߰�
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
			tree->count++;		//���� �߰��Ϸ��� �������� value�� �̹� �����ϸ� count����
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

