// ���� ���Ͽ� �̾� ���� ��� "a" 


#include<stdio.h>
//#include<limits.h> // �� �ִ밪
//INT_INF
#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];
int num[MAX_VERTICES];

void set_init(int n) {
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
		num[i] = 1;
	}
}


// return ultimate ancestor of given vertex
int set_find(int vertex) {   // ��� ������ ����Ѵ�. 
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p); // ��ǥ ��带 s�� �����Ѵ�.

	s = i;

	for (i = vertex; (p = parent[i]) >= 0; i = p)  // ��ο� �ִ� ��� ���� ��ǥ���� �ٲپ� ��� ��θ� ���� �ʵ��� �����Ѵ�. 
		parent[i] = s;

	return s;
}

void set_union(int s1, int s2) {
	if (num[s1] < num[s2]) {  // ���� s1�� ���� ������ ũ�Ⱑ s2���� ������
		parent[s1] = s2;	  // s1�� �θ���� s2�� �����Ѵ�.
		num[s2] += num[s1];   // s2������ ũ�⿡ s1������ ũ�⸦ ���Ѵ�. 
	}
	else { // �ݴ��� ���
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

typedef struct {
	int u;
	int v;
	int weight;
}element;

typedef struct {
	element heap[MAX_VERTICES];
	int heap_size;
}HeapType;

void init(HeapType* h) {
	h->heap_size = 0; // �ε��� 1���� ����ϱ� ������ 0���� �ʱ�ȭ
}

int is_empty(HeapType* h) {
	if (h->heap_size == 0)
		return 1;
	else
		return 0;
}

void insert_min_heap(HeapType* h, element item) {
	int i;

	i = ++(h->heap_size);

	while ((i != 1) && (item.weight < h->heap[i / 2].weight)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_min_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];

	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].weight) > h->heap[child + 1].weight)
			child++;

		if (temp.weight <= h->heap[child].weight)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item; 
}
/*     // �ϳ��� ���� ����
void insert_heap_edge(HeapType* h, int u, int v, int weight) {
	element e;

	e.u = u;
	e.v = v;
	e.weight = weight;
	insert_min_heap(h, e);
}*/

void insert_all_edges(HeapType* h) {
	FILE* fp;
	element e;

	fopen_s(&fp, "data5.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "������ �� �� ����\n");
		return;
	}

	while (!feof(fp)) {
		fscanf_s(fp, "%d %d %d" , &e.u, &e.v, &e.weight);
		insert_min_heap(h, e);
	}
	fclose(fp);
}

void kruskal(int n) {
	HeapType h;
	element e;
	int edge_accpted = 0;  // ������� ���õ� ������ ��
	int uset, vset;        // ���� u�� ���� v�� ���� ��ȣ

	init(&h);
	insert_all_edges(&h);
	set_init(n);

	while (edge_accpted < (n - 1)) {
		e = delete_min_heap(&h);
		//from to weight
		uset = set_find(e.u);  // ���� u�� ���� ��ȣ
		vset = set_find(e.v);  // ���� v�� ���� ��ȣ

		if (uset != vset) {    // ���� ���� ������ �ٸ���
			printf("(%d %d) %d\n", e.u, e.v, e.weight);
			edge_accpted++;
			set_union(uset, vset);  // �ΰ��� ������ ��ģ��. 
		}// end of if
	}// end of while
}

int main() {
	FILE* fp;
	int max;
	element e;

	fopen_s(&fp, "data5.txt", "r");
	if (fp == NULL) {
		printf(stderr, "������ �� �� ����");
		return 0;
	}

	max = 0;

	while (!feof(fp)) {
		fscanf_s(fp, "%d %d %d", &e.u, &e.v, &e.weight);
		if (e.v > max)
			max = e.v;
	}

	kruskal(max + 1);
	fclose(fp);
	return 0;
}