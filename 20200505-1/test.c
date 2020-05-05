#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct Heap {
	int* array;
	int size;
	int capacity;
}Heap;

//��������
void Swap(int* array, int child, int parent) {
	int tmp = array[child];
	array[child] = array[parent];
	array[parent] = tmp;
}
//���µ���
void ShiftDown(int* array, int n, int parent) {
	int child = 2 * parent + 1;
	while (child < n) {
		if (child + 1 < n&&array[child + 1] > array[child])
			child++;
		if (array[parent] < array[child]) {
			Swap(array, child, parent);
			parent = child;
			child = 2 * parent + 1;
		}
		else
			break;
	}
}
//�������µ������� 
void CreatHeap(Heap* hp, int* array, int n) {
	hp->array = (int*)malloc(sizeof(int)*n);
	hp->capacity = n;
	hp->size = n;
	memcpy(hp->array, array, sizeof(int)*n);
	for (int i = (n - 2) / 2; i >= 0; i--) {
		ShiftDown(hp->array, n, i);
	}
}

//���ϵ���
void ShiftUp(int* array, int child) {
	int parent = (child - 1) / 2;
	while (child > 0) {
		if (array[child] > array[parent]) {
			Swap(array, child, parent);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
			break;
	}
}
//����
void HeapPush(Heap* hp, int data) {
	if (hp->size == hp->capacity) {
		hp->capacity *= 2;
		hp->array = (int*)realloc(hp->array, hp->capacity * sizeof(int));
	}
	//β��
	hp->array[hp->size++] = data;
	//���ϵ���
	ShiftUp(hp->array, hp->size - 1);
}
//ɾ���Ѷ�Ԫ��
void HeapPop(Heap* hp) {
	if (hp->size > 0) {
		Swap(hp->array, 0, hp->size - 1);
		hp->size--;
		ShiftDown(hp->array, hp->size, 0);
	}
}

int HeapEmpty(Heap* hp) {
	if (hp->size == 0)
		return 1;
	return 0;
}

void HeapPrint(Heap* hp) {
	for (int i = 0; i < hp->size; i++) {
		printf("%d ", hp->array[i]);
	}
	printf("\n");
}

//������
void HeapSort(int* array, int size) {
	for (int i = (size - 2) / 2; i >= 0; i--) {
		ShiftDown(array, size, i);
	}
	while (size > 1) {
		Swap(array, 0, size - 1);
		size--;
		ShiftDown(array, size, 0);
	}
}

void test() {
	Heap hp;
	int array[] = { 100,50,30,20,25,18,10,5,15,21,23 };
	int size = sizeof(array) / sizeof(array[0]);
	CreatHeap(&hp, array, size);
	HeapPrint(&hp);
}

int main() {
	test();
	system("pause");
	return 0;
}