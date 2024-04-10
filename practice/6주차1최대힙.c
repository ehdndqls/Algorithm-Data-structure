#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 100

typedef struct {
	int key; // �켱����
	char animal[MAX_LEN];
}element;

typedef struct {
	int heap_size;
	element heap[MAX_LEN];
}HeapType;

void init(HeapType* h)
{
	h->heap_size = 0;
}

// upheap
void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	// ��Ʈ��尡 �ƴϰ� && ���� ����� �θ� ��庸�� ũ��
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;
}

void display(HeapType* h)
{
	int i;
	for (i = 1; i < h->heap_size + 1; i++) {
		printf("%d : %s > ", h->heap[i].key, h->heap[i].animal);
	}
	printf("\n\n");
}

int main() {
	FILE* fp;
	fopen_s(&fp,"data3.txt", "r");
	if (fp == NULL) exit(1);

	element tmp;
	HeapType heap;
	init(&heap);

	while (!feof(fp)) {
		fscanf_s(fp, "%d %s", &tmp.key, tmp.animal, MAX_LEN);
		printf("%d %s\n", tmp.key, tmp.animal);

		insert_max_heap(&heap, tmp);
		display(&heap);
	}

	while (1) {
		printf("������ �켱������ �̸��� �Է��Ͻÿ�(0: �Ϸ�) \n");
		printf(">> ");
		scanf_s("%d", &tmp.key);

		if (tmp.key != 0) {
			scanf_s("%s", tmp.animal, MAX_LEN);
			insert_max_heap(&heap, tmp);
			display(&heap);
		}
		else break;
	}

	fclose(fp);
	return 0;
}