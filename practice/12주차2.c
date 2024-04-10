#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int seq_search(int key, int low, int high, int list[]) {
	int i;
	for (i = low; i < high; i++)
		if (list[i] == key)
			return i;

	return -1;
}

int seq2_search(int key, int low, int high, int list[]) {
	int i;
	list[high + 1] = key;

	for (i = low; list[i] != key; i++);

	if (i == (high + 1))
		return -1;
	else
		return i;
}


int main() {
	FILE* fp;
	int count = 0;
	int i;
	int* list = NULL;

	int KEY = -1;
	clock_t start, end, start2, end2;
	float seq_time, seq2_time;
	int result, result2;

	fp = fopen("data13.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%5d", &i);
		count++;
	}

	rewind(fp);

	list = (int*)malloc(sizeof(int) * (count + 1));
	count = 0;

	while (!feof(fp)) {
		fscanf(fp, "%d", &list[count]);
		count++;
	}

	printf("������ ����: %d\n", count);
	printf("�˻��ϴ� ������ �Է��Ͻÿ�: ");
	scanf("%d", &KEY);

	start = clock();
	result = seq_search(KEY, 0, count - 1, list);
	end = clock();

	start2 = clock();
	result2 = seq2_search(KEY, 0, count - 1, list);
	end2 = clock();

	seq_time = (float)(end - start) / CLOCKS_PER_SEC;
	seq2_time = (float)(end2 - start2) / CLOCKS_PER_SEC;

	if (result != -1 && result2 != -1) {
		printf("Ž�� ����\n");
		printf("�����˻� �ӵ�: %f\n", seq_time);
		printf("������ �����˻� �ӵ�: %f\n", seq2_time);
	}
	else {
		printf("Ž�� tlfvo\n");
		printf("�����˻� �ӵ�: %f\n", seq_time);
		printf("������ �����˻� �ӵ�: %f\n", seq2_time);
	}
	
	free(list);
	fclose(fp);
	return 0;
}