#include <stdio.h>
#include <iostream>
#define N 4
using namespace std;

int a[N];
void perm(int); /*求陣列的全排列 */
void printnum();
void swap(int, int);
int main() {
	int i;
	for (i = 0; i < N; i++) {
		a[i] = i + 1;
	}
	perm(0);
	system("pause");
	return 0;
}
void perm(int offset) {
	int i, temp;
	if (offset == N/2) {  // BaseCase
		printnum();
		return;
	}
	else {
		for (i = offset; i < N; i++) {
			swap(i, offset);//交換字首
			perm(offset+1);//遞迴
			swap(i, offset);//將字首換回來，繼續做前一次排列
		}
	}
}
void printnum() {
	int i;
	for (i = 0; i < N; i++)
		cout << a[i] << "  ";
	cout << endl;
}
void swap(int i, int offset) {
	int temp;
	temp = a[offset];
	a[offset] = a[i];
	a[i] = temp;
}
