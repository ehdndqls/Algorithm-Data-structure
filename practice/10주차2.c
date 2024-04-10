#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

typedef struct {
	char name[20];
	int student_no;
	int rank;
}element;

void print_list(element list[], int n) {
	printf("____________________________\n");
	for (int i = 0; i < n; i++)
		printf("| %-7s | %-8d | %-2d | \n", list[i].name, list[i].student_no, list[i].rank);
	printf("____________________________\n");
}

void selection_sort(element list[], int n) {
	int i, j, least;
	element temp;

	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++)
			if (list[j].rank < list[least].rank)
				least = j;

		// 가장 작은 least 찾은 상태
		temp = list[i];
		list[i] = list[least];
		list[least] = temp;
	}
}

int main() {
	FILE* fp;
	int count = 0;
	element temp;
	element* list;

	fp = fopen("data9.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%s %d %d", temp.name, &temp.student_no, &temp.rank);
		count++;
	}
	list = (element*)malloc(sizeof(element) * count);
	rewind(fp);

	count = 0;
	while (!feof(fp)) {
		fscanf(fp, "%s %d %d", list[count].name, &list[count].student_no, &list[count].rank);
		count++;
	}

	printf("정렬전\n");
	print_list(list, count);
	
	selection_sort(list, count);
	printf("등수 선택정렬\n");
	print_list(list, count);

	fclose(list);
	free(fp);
	return 0;
}

