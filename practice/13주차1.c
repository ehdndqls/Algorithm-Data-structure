#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int binary_search(int key, int first, int end, int list[]) {
	int middle;

	while (first <= end) {
		middle = (first + end) / 2;
		if (key == list[middle])
			return middle;
		else if (key > list[middle])
			first = middle + 1;
		else
			end = middle - 1;
	}
	return -1;
}

int main() {
	FILE* fp;
	int count = 0;
	int i = 0;
	int* list = NULL;
	int key = 0;
	clock_t start, end;
	float result;
	int flag;


	fp = fopen("data13.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%d", &i);
		count++;
	}
	rewind(fp);

	list = (int*)malloc(sizeof(int) * count);

	count = 0;
	while (!feof(fp)) {
		fscanf(fp, "%d", &list[count]);
		count++;
	}

	printf("찾고자 하는 정수를 입력하시오: ");
	scanf("%d", &key);
	start = clock();
	flag = binary_search(key, 0, count - 1, list);
	end = clock();

	result = (float)(end - start) / CLOCKS_PER_SEC;

	if (flag == -1)
		printf("탐색 실패\n");
	else {
		printf("탐색 성공\n");
		printf("%d번째 인덱스서 검색 성공\n", flag + 1);
		printf("이진탐색 실행 시간: %f\n\n", result);
	}


	free(list);
	fclose(fp);

	return 0;
}