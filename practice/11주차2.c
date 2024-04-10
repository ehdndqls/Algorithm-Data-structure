#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define SIZE 64


typedef struct {
	char name[64];
	int id;
	char num[16];
}Student;

Student list[SIZE] = { 0 };
int listSize = 0;


void printList() {
	for (int i = 0; i < listSize; i++) {
		printf("%s %d %s\n", list[i].name, list[i].id, list[i].num);
	}
}

void insertSort(int start, int end, int gap) {
	int j;
	Student key;
	for (int i = start + gap; i <= end; i += gap) {
		key = list[i];
		for (j = i - gap; j >= start && key.id > list[j].id; j -= gap)	
			list[j + gap] = list[j];
		list[j + gap] = key;	
	}
}

void shellSort() {
	int gap;
	for (gap = listSize / 2; gap > 0; gap /= 2) {
		for (int i = 0; i < gap; i++)
			insertSort(i, listSize - 1, gap);
	}
}


int main() {
	FILE* fp = fopen("data11.txt", "r");
	
	if (!fp) {
		printf("file load error\n");
		return -1;
	}
	Student tmp;
	int i = 0;
	while(!feof(fp)){
		fscanf(fp, "%s %d %s", &tmp.name, &tmp.id, &tmp.num);
		list[i] = tmp;
		listSize++;
		i++;
	}
	printf("< 정렬 전 데이터 >\n");
	printList();
	printf("\n\n");

	shellSort();

	printf("< 정렬 후 데이터 >\n");
	printf("※ 내림차순\n");
	printList();
	printf("\n\n");

	return 0;
}