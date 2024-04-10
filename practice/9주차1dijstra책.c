#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define VERTICES 7
#define INF 1000	// 무한대
#define TRUE 1
#define FALSE 0

int distance[VERTICES]; // 시작 정점으로부터의 최단 경로 거리
int found[VERTICES] = { 0 }; // 방문한 정점 표시


typedef struct Graph {
	int num;
	int weight[VERTICES][VERTICES];
}Graph;

Graph* createGraph() {
	Graph* tmp = (Graph*)malloc(sizeof(Graph));
	tmp->num = VERTICES;
	for (int i = 0; i < VERTICES; i++) {
		for (int j = 0; j < VERTICES; j++) {
			if (i == j) tmp->weight[i][j] = 0;
			else tmp->weight[i][j] = INF;
		}
	}
	return tmp;
}

void printGraphMatrix(Graph* g) {
	for (int i = 0; i < VERTICES; i++) {
		for (int j = 0; j < VERTICES; j++)
			printf("%4d ", g->weight[i][j]);
		printf("\n");
	}
}

void insertEdge(Graph* g, int u, int v, int w) {
	g->weight[u][v] = w;
	g->weight[v][u] = w;
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
	printf("Distance: ");
	for (int i = 0; i < num; i++)
		printf("%4d  ", distance[i]);
	printf("\n");
	printf("Found   : ");
	for (int i = 0; i < num; i++)
		printf("%4d  ", found[i]);
	printf("\n\n");
}

void dijkstra(Graph* g, int start) {
	for (int i = 0; i < g->num; i++) {	// array initialize
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}

	found[start] = TRUE;
	distance[start] = 0;

	for (int i = 0; i < g->num; i++) {
		printf("Step %d.\n", i + 1);
		printDistance(g->num);
		int u = selectMin(g->num);
		printf("select: %d\n", u);
		found[u] = TRUE;
		for (int v = 0; v < g->num; v++) {
			if (found[v] == 0) {
				printf("compare: d[%d]+[%d][%d] = %d, d[%d] = %d\n", u, u, v, distance[u] + g->weight[u][v], v, distance[v]);;
				if (distance[u] + g->weight[u][v] < distance[v])
					distance[v] = distance[u] + g->weight[u][v];
				// 기존 경로보다 짧으면 갱신
			}
		}
	}
}


int main() {
	FILE* fp = fopen("data6.txt", "r");
	if (!fp) {
		printf("file eror\n");
		return -1;
	}

	Graph* g = createGraph();

	int u, v, w;
	while (fscanf(fp, "%d %d %d", &u, &v, &w) != EOF) {
		insertEdge(g, u, v, w);
	}

	printGraphMatrix(g);

	dijkstra(g, 0);

	free(g);
	fclose(fp);

	return 0;
}

