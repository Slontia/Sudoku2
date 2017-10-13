#include "stdafx.h"
#include"ctime"  
#include"cstdlib"

int get_valuebit(Box* member) {
	return (1 << ((member->cervalue) - 1));
}
int get_valuebit(int value) {
	return (1 << value);
}

int count_one(int value) {
	int counter = 0;
	while (value) {
		value &= value - 1;
		counter++;
	}
	return counter;
}

int get_one(int vect) {
	int rightmost;
	for (int i = 0; i < SIZE; i++, vect = (vect >> 1)) {
		rightmost = vect & 0x1;
		if (rightmost == 1) {
			assert(i<9);
			return i;
		}
	}
	assert(0);
	return -1;
}

void display_2d(int** two_d, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << two_d[i][j] << " ";
		}
		cout << endl;
	}
}

void display_1d(int* two_d, int m, int cluster) {
	cout << "display:" << endl;
	for (int i = 0; i < m; i++) {
		cout << two_d[i] << " ";
		if ((cluster != 0) && ((i+1) % cluster == 0)) {
			cout << endl;
		}
	}
	cout << endl;
}

bool read_file(FILE* f, int sudoku[SIZE*SIZE])
{
	int readin = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int d;
			readin += fscanf_s(f, "%d", &d);
			sudoku[9 * i + j] = d;
		}
	}
	return readin == 81;
}

  
#define MAX 20000  

struct element {     //������������ݽṹ   
	int data;  // ����   
	int index;  // ���   
};
int cmp(const void *a, const void *b); //��������   
void rand_of_n(int a[], int n);  //���� 1-n ��������в��浽 a[] ��   
int main_rand_of_n() {
	int a[MAX];
	int i, n = 10;
	rand_of_n(a, n);
	for (i = 0; i<n; i++)
		cout << a[i] << " ";
	return 0;
}

int cmp(const void *a, const void *b) {   // ��������  
	return((struct element*)a)->data - ((struct element*)b)->data;
}
void rand_of_n(int a[], int n) {
	int i;
	struct element ele[MAX];
	for (i = 0; i<n; i++) {
		ele[i].data = rand();  // �������һ����   
		ele[i].index = i + 1;
	}
	qsort(ele, n, sizeof(ele[0]), cmp);  //����   
	for (i = 0; i<n; i++) {
		a[i] = ele[i].index;
	}
}