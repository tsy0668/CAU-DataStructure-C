#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define TRUE 1
#define FALSE 0
#define numRow 10
#define numCol 10
#define DST_ROW 5 //������ ��ǥ row
#define DST_COL 6 //������ ��ǥ col
#define stack_size 100

typedef struct {
	int row;  int col; int dir_vector; //direction vector�� ���� ������ �Ʒ� ����
} element;

typedef struct {
	short int vert; short int horiz;
} offsets;

void setup_maze();
void set_move();
void path();
int init_dir_vector(int row, int col); //�Լ� ���ǿ��� ����
int get_next_dir(int dir_vector); //�Լ� ���ǿ��� ����
void push(element position);
element pop();

int top = -1;
offsets move[8];
short int maze[numRow + 2][numCol + 2];
element stack[stack_size];


void main() {
	setup_maze();
	set_move();
	path();
}

void setup_maze() {
	int i, j;
	short int maze0[numRow][numCol] = {
	{ 0,0,1,0,1,1,1,0,1,0 },
	{ 1,0,0,1,1,1,0,1,0,1 },
	{ 1,1,0,1,1,0,1,0,1,1 },
	{ 0,0,1,0,1,1,1,0,0,0 },
	{ 0,1,1,0,1,0,1,0,1,0 },
	{ 1,0,1,1,1,1,0,0,1,0 },
	{ 1,1,0,1,0,1,0,0,1,0 },
	{ 1,0,0,0,1,0,1,0,0,0 },
	{ 0,1,0,1,1,1,0,1,1,0 },
	{ 1,0,0,1,1,1,0,0,0,0 }
	};

	//������ ��ǥ�� �Ա� (1,1)�� ����
	if (DST_ROW == 1 && DST_COL == 1) {
		printf("\nThe coordinate of destination should be different from that of entrance (1,1).");
		exit(0);
	}
	//�������� block�Ǿ� ���� �ʵ��� �Ѵ�.
	if (maze0[DST_ROW - 1][DST_COL - 1] == 1) {
		printf("\nmaze[DST_ROW][DST_COL] should be 0.");
		exit(0);
	}

	for (i = 0; i < numCol + 2; i++) maze[0][i] = 1;
	for (i = 0; i < numCol + 2; i++) maze[numRow + 1][i] = 1;
	for (i = 0; i < numRow + 2; i++) maze[i][0] = 1;
	for (i = 0; i < numRow + 2; i++) maze[i][numCol + 1] = 1;
	for (i = 1; i <= numRow; i++)
		for (j = 1; j <= numCol; j++) maze[i][j] = maze0[i - 1][j - 1];
}

void set_move() {
	move[0].vert = -1; move[0].horiz = 0;
	move[1].vert = -1; move[1].horiz = 1;
	move[2].vert = 0; move[2].horiz = 1;
	move[3].vert = 1; move[3].horiz = 1;
	move[4].vert = 1; move[4].horiz = 0;
	move[5].vert = 1; move[5].horiz = -1;
	move[6].vert = 0; move[6].horiz = -1;
	move[7].vert = -1; move[7].horiz = -1;
}

void push(element position) {
	stack[++top] = position;
}

element pop() {
	element position;

	position = stack[top--];
	return position;
}

void path() {
	int i, row, col, nextRow, nextCol, dir, dir_vector, found = FALSE;
	element position;

	row = 1; col = 1;
	maze[1][1] = -1;
	dir_vector = init_dir_vector(1, 1);
	if (dir_vector == -1) found = TRUE; //(1,1)�� �ٷ� �̿��� �������� ����
	else {
		top = 0;
		stack[0].row = 1; stack[0].col = 1; stack[0].dir_vector = dir_vector;
	}
	while (top > -1 && !found) {
		position = pop();

		////////////////////////////��////////////////////////
		row = position.row;
		col = position.col;
		dir_vector = position.dir_vector;
		dir = 0;
		//////////////////////////////////////////////////////

		while (dir < 8 && !found) {
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;

			/////////////////��/////////////////////////////////
			if (nextRow == DST_ROW && nextCol == DST_COL)
				found = TRUE;
			else if (!maze[nextRow][nextCol]) {
				maze[nextRow][nextCol] = -1;
				position.row = row;
				position.col = col;
				position.dir_vector = get_next_dir(dir_vector);
				push(position);
				row = nextRow;
				col = nextCol;
				dir = 0;
			}

			else ++dir;
			////////////////////////////////////////////////////
		}
	}
	if (found) {
		printf("The path is:\n");
		printf("row  col\n");
		for (i = 0; i <= top; i++) printf("%2d%5d\n", stack[i].row, stack[i].col);
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", DST_ROW, DST_COL);
	}
	else printf("The maze does not have a path\n");
}

int init_dir_vector(int row, int col) {
	// input: ��ġ ��ǥ
	// output: -1 �Ǵ� 0 ~ 255(=2^8-1) ������ ������
	//
	// ��ġ (row, col)�� 8 ���� �̿� �� �������� ������ -1�� return (�Ͽ� ��� ã�⸦ �����ϰ� �Ѵ�), 
	// ������ 0 ~ 255(=2^8-1) ������ ���������� ǥ���� direction vector�� �ʱ�ȭ�Ͽ� return
	//
	// direction vector: 8-bit string���� �� ũ�⿡ �ش��ϴ� ���������� ǥ���ȴ�
	// least significant bit���� 0��, 1��, ..., 7�� bit��� �θ���
	// i�� bit�� ���� i�� ���� (i=0,...,7). ��: 0�� bit�� north, 1�� bit�� north-east, ...
	// i�� bit=1: ���� i�� ��� ã�⿡�� �̹� try�ߴٴ� ���� ǥ��
	// i�� bit=0: ���� i�δ� ���� ������ �ʾҴٴ� ���� ǥ��
	// ��ġ (row, col)�� direction vector �ʱ�ȭ: ��ġ (row, col)�� 8 ���� ������ ����, block�Ǿ� �� �� ���ų�
	// �̹� ���� �����̸� direction vector�� �ش� bit�� 1��, �׷��� ������ 0���� set.
	// �ʱ�ȭ ���� ��� (�Ʒ� �ڵ�): ó���� 8 bits�� ��� 1�� set�� ��, �� ���� ���� üũ�Ͽ� �� �� ������ �ش� bit�� 0���� reset

	int dir, nextRow, nextCol, dir_vector;

	dir_vector = ((int)pow(2.0, 8.0)) - 1; // dir_vector = 10������ 255, �������� 11111111 (8 bit ��� 1)
	for (dir = 0; dir < 8; dir++) {
		nextRow = row + move[dir].vert;
		nextCol = col + move[dir].horiz;
		if (nextRow == DST_ROW && nextCol == DST_COL) return -1; // to report that a path is found
		if (!maze[nextRow][nextCol]) dir_vector -= (int)pow(2.0, (double)dir);
	}
	return dir_vector;
}

int get_next_dir(int dir_vector) {
	// input: direction vector (0 ~ 255(=2^8-1) ������ ������)
	// output: ���Ⱚ 0..7 �Ǵ� 8
	//
	// direction vector�� ǥ���� �������� �޾Ƽ� 8 bits ������ 1 �Ǵ� 0 ���� 
	// ũ�� 8�� �迭 (�Ʒ� �ڵ��� d[8] �迭)�� �ű� ��
	// 0�� bit �� �ϳ��� random�ϰ� �����Ͽ� �� bit�� �ش�Ǵ� ���Ⱚ (0..7)�� return
	// ���� 0�� bit�� �ϳ��� ������ 8�� return (�Ͽ� backtrack�� �����ϰ� �Ѵ�)

	int dir, d[8], count, k;

	for (dir = 0; dir < 8; dir++) {
		d[dir] = dir_vector % 2;
		dir_vector /= 2;
	}

	// count = direction vector���� 0 bit�� ����
	count = 0;
	for (dir = 0; dir < 8; dir++) if (d[dir] == 0) count++;

	if (count == 0) return 8;

	// count���� 0 bit �� �ϳ��� random�ϰ� �����Ͽ� �ش� ���Ⱚ (0..7)�� return
	k = rand() % count + 1;
	for (dir = 0; dir < 8; dir++) {
		if (d[dir] == 0) k--;
		if (k == 0) return dir;
	}
}