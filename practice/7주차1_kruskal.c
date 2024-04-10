// 기존 파일에 이어 쓰는 방법 "a" 


#include<stdio.h>
//#include<limits.h> // 각 최대값
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
int set_find(int vertex) {   // 경로 압축을 사용한다. 
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p); // 대표 노드를 s에 저장한다.

	s = i;

	for (i = vertex; (p = parent[i]) >= 0; i = p)  // 경로에 있는 모든 것을 대표노드로 바꾸어 모든 경로를 돌지 않도록 압축한다. 
		parent[i] = s;

	return s;
}

void set_union(int s1, int s2) {
	if (num[s1] < num[s2]) {  // 만약 s1이 속한 집합의 크기가 s2보다 작으면
		parent[s1] = s2;	  // s1의 부모노드로 s2를 설정한다.
		num[s2] += num[s1];   // s2집합의 크기에 s1집합의 크기를 더한다. 
	}
	else { // 반대의 경우
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
	h->heap_size = 0; // 인덱스 1부터 사용하기 때문에 0으로 초기화
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
/*     // 하나씩 간선 삽입
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
		fprintf(stderr, "파일을 열 수 없음\n");
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
	int edge_accpted = 0;  // 현재까지 선택된 간선의 수
	int uset, vset;        // 정점 u와 정점 v의 집합 번호

	init(&h);
	insert_all_edges(&h);
	set_init(n);

	while (edge_accpted < (n - 1)) {
		e = delete_min_heap(&h);
		//from to weight
		uset = set_find(e.u);  // 정점 u의 집합 번호
		vset = set_find(e.v);  // 정점 v의 집합 번호

		if (uset != vset) {    // 서로 속한 집합이 다르면
			printf("(%d %d) %d\n", e.u, e.v, e.weight);
			edge_accpted++;
			set_union(uset, vset);  // 두개의 집합을 합친다. 
		}// end of if
	}// end of while
}

int main() {
	FILE* fp;
	int max;
	element e;

	fopen_s(&fp, "data5.txt", "r");
	if (fp == NULL) {
		printf(stderr, "파일을 열 수 없음");
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