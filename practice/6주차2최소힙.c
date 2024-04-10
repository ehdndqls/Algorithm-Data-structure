#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 100

typedef struct {
	int key;
	char name[MAX_LEN];
}element;

typedef struct {
	int heap_size;
	element heap[MAX_LEN];
}HeapType;
 
void init(HeapType* h)
{
	h->heap_size = 0;
}

void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;
}

element delete_min_heap(HeapType* h)
{
	element item, temp;
	int parent, child;

	item = h->heap[1];                // [1] = root(�ּҰ�)
	temp = h->heap[(h->heap_size)--]; // ��Ʈ���� ���� �������� �ִ� ��� , (������ ���� ������ �ϳ� ���ҽ�Ŵ)

	parent = 1;
	child = 2; // left sub child

	while (child <= h->heap_size) {
		// ���� ����� �ڽ� ��� �߿� �� ���� �ڽ� ��带 ã�´�.
		if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key)) {
			child++;
		}
		if (temp.key <= h->heap[child].key) {
			break;
		}

		//�Ѵܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;
	printf(">> �մ�(%s) ����\n", item.name);

	for (int k = 1; k < h->heap_size + 1; k++) {
		h->heap[k].key--;
	}

	return item;
}

void inorder(HeapType* h, int key)
{
	if (key <= h->heap_size) {
		// left -> root -> right
		inorder(h, key * 2);
		printf("%d - %s\n", h->heap[key].key, h->heap[key].name);
		inorder(h, (key * 2) + 1);
	}
}

int main() {
	FILE* fp;
	fopen_s(&fp,"data4.txt", "r");
	if (fp == NULL) exit(1);

	element tmp;
	char cmd;
	int count = 1;
	HeapType heap;

	init(&heap);

	while (!feof(fp)) {
		fscanf_s(fp, "%c", &cmd,1);

		switch (cmd)
		{
		case 'i':
			fscanf_s(fp, "%s", &tmp.name, MAX_LEN);
			printf(">> �մ�(%s) ����\n", tmp.name);
			tmp.key = count;
			insert_min_heap(&heap, tmp);

			printf("< ���� ���� ��ȸ ��� >\n");
			inorder(&heap, 1);
			printf("\n");
			count++;
			break;
		case 'o':
			delete_min_heap(&heap);
			count--;

			printf("< ���� ���� ��ȸ ��� >\n");
			inorder(&heap, 1);
			printf("\n");
			break;
		default:
			break;
		}
	}

	fclose(fp);
	return 0;
}