#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000L

typedef struct {
	int u;
	int v;
	int key;
}element;

int weight[MAX_VERTICES][MAX_VERTICES];
int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

int get_min_vertex(int n) {
	int v, i;

	for (i = 0; i < n; i++)
		if (!selected[i]) {
			v = i;
			break;
		}

	for (i = 0; i < n; i++)
		if (!selected[i] && (distance[i] < distance[v])) 
			v = i;

	return v;
}

void prim(int s, int n) {
	int i;
	int u, v;
	for (u = 0; u < n; u++) {
		distance[u] = INF;
		selected[u] = FALSE;
	}

	distance[s] = 0; // {0,INF,INF,INF,....}

	// prim main loop starts
	for (i = 0; i < n; i++) {
		u = get_min_vertex(n);
		selected[u] = TRUE;

		if (distance[u] == INF)
			return;

		printf("%d", u);

		// distancearray update
		for (v = 0; v < n; v++)
			if (weight[u][v] != INF)
				if (!selected[v] && weight[u][v] < distance[v])
					distance[v] = weight[u][v];
	}
}

int main() {
	FILE* fp;
	element e;
	int max;
	int i, j;

	fopen_s(&fp, "data5.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "파일을 열 수 없습니다.\n");
		return 0;
	}

	max = 0;
	while (!feof(fp)) {
		fscanf_s(fp, "%d %d %d", &e.u, &e.v, &e.key);
		if (e.v > max)
			max = e.v;
	}

	max += 1;
	rewind(fp); // 파일을 제일 앞부분으로 땡겨옴

	for (i = 0; i < max; i++)
		for (j = 0; j < max; j++)
			if (i == j)
				weight[i][j] = 0;
			else
				weight[i][j] = INF;

	while (!feof(fp)) {
		fscanf_s(fp, "%d %d %d", &e.u, &e.v, &e.key);
		weight[e.u][e.v] = e.key;
		weight[e.v][e.u] = e.key;
	}
	
	prim(0, max);
	printf("\n");
	fclose(fp);
	return 0;
}