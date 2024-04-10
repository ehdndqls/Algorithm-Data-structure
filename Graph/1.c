#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 50

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

void init(GraphType* g) {
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX_VERTICES; r++) {
        for (c = 0; c < MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
    }
}

void insert_vertex(GraphType* g, int v) {
    if ((g->n + 1) > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 개수 초과");
        return;
    }
    g->n++;
}

void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    g->adj_mat[start][end] = 1;
}

void find_cycles(GraphType* g, bool visited[], int start, int current, int path[], int length) {
    visited[current] = true;
    path[length] = current;

    for (int i = 0; i < g->n; i++) {
        if (g->adj_mat[current][i] == 1) {
            if (i == start && length >= 2) {
                // 사이클을 찾았을 때 출력
                printf("사이클: ");
                for (int j = 0; j <= length; j++) {
                    printf("%d ", path[j]);
                }
                printf("\n");
            }
            if (!visited[i]) {
                find_cycles(g, visited, start, i, path, length + 1);
            }
        }
    }

    visited[current] = false;
}

void find_all_cycles(GraphType* g) {
    bool visited[MAX_VERTICES] = { false };
    int path[MAX_VERTICES];

    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            if (g->adj_mat[i][j] == 1) {
                find_cycles(g, visited, i, i, path, 0);
                visited[i] = true;
            }
        }
        visited[i] = true;
    }
}

int main() {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    init(g);

    for (int i = 0; i < 6; i++)
        insert_vertex(g, i);

    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 1, 3);
    insert_edge(g, 2, 4);
    insert_edge(g, 3, 0);
    insert_edge(g, 3, 4);
    insert_edge(g, 4, 1);
    insert_edge(g, 4, 2);
    insert_edge(g, 5, 4);

    find_all_cycles(g);

    free(g);
    return 0;
}
