#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define VERTICES 5
#define MAX 100
#define INF 1000L
#define TRUE 1
#define FALSE 0

int distance[MAX];
int found[MAX] = { 0 };


typedef struct Graph {
	int n;
	int weight[MAX][MAX];
}Graph;

Graph* createGraph() {
	Graph* tmp = (Graph*)malloc(sizeof(Graph));
	tmp->n = VERTICES;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (i == j)
				tmp->weight[i][j] = 0;
			else
				tmp->weight[i][j] = INF;
		}
	}
	return tmp;
}

void printGraphMatrix(Graph* g) {
	for (int i = 0; i < VERTICES; i++) {
		for (int j = 0; j < VERTICES; j++)
			if (g->weight[i][j] == INF)
				printf(" INF ");
			else
				printf("%4d ", g->weight[i][j]);
		printf("\n");
	}
}

void insertNode(Graph* g, int u, int v, int w) {
	g->weight[u][v] = w;
}

int selectMin(int num) {
	int minpos = -1, min = INF;

	for (int i = 0; i < num; i++) {
		if (distance[i] < min
			&& found[i] == 0) {	// less than min & not found
			minpos = i;
			min = distance[i];
		}
	}

	return minpos;
}

void printDistance(num) {
	printf("Select  : { ");
	for (int i = 0; i < num; i++)
		if (found[i] == 1)
			printf("%c ", i + 'A');
	printf("}\n");

	printf("Distance: {");
	for (int i = 0; i < num; i++)
		if (distance[i] == INF) printf("INF ");
		else printf("%3d ", distance[i]);
	printf("}\n\n");
}

void daijkstra(Graph* g, int start) {
	for (int i = 0; i < g->n; i++) {	// array initialize
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}

	found[start] = TRUE;
	distance[start] = 0;

	for (int i = 0; i < g->n; i++) {
		printf("Step %d.\n", i + 1);
		printDistance(g->n);
		int u = selectMin(g->n);
		found[u] = TRUE;
		for (int v = 0; v < g->n; v++) {
			if (found[v] == 0) {
				if (distance[u] + g->weight[u][v] < distance[v])
					distance[v] = distance[u] + g->weight[u][v];
				// 기존 경로보다 짧으면 갱신
			}
		}
	}
}


int main() {
	FILE* fp = fopen("data7.txt", "r");
	if (!fp) {
		printf("file load error\n");
		return -1;
	}

	Graph* g = createGraph();

	int u, v, w;
	while (fscanf(fp, "%d %d %d", &u, &v, &w) != EOF) {
		insertNode(g, u, v, w);
	}

	printf("*****가중치 인접 행렬***** \n");
	printGraphMatrix(g);
	printf("\n\n");
	printf("*****다익스트라 최단경로 구하기***** \n");
	daijkstra(g, 0);
}

