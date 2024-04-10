#include<stdio.h>
#define MAX_LIST_SIZE 256
#define INDEX_SIZE 256

int list[MAX_LIST_SIZE];

typedef struct {
	int key;
	int index;
}itable;

itable index_list[INDEX_SIZE];

int seq_search(int key, int low, int high) {
	int i;

	for (i = low; i <= high; i++)
		if (list[i] == key)
			return i;
	return -1;
}

int seq_search2(int key, int low, int high) {
	int i;
	
	list[high + 1] = key;
	for(i = low; list[i] != key; i++)
		;
	if (i == (high + 1)) return -1;
	else return i;
}

int search_binary(int key, int low, int high) {
	int middle;

	if (low <= high) {
		middle = (low + high) / 2;
		if (key == list[middle])
			return middle;
		else if (key < list[middle])
			return search_binary(key, low, middle - 1);
		else
			return search_binary(key, middle + 1, high);
	}
	return -1;
}

int search_binary2(int key, int low, int high) {
	int middle;

	while (low <= high) {
		middle = (low + high) / 2;
		if (key == list[middle])
			return middle;
		else if (key > list[middle])
			low = middle + 1;
		else
			high = middle - 1;
	}
	return -1;
}

// INDEX_SIZE�� �ε��� ���̺��� ũ��, n�� ��ü �������� ��
int search_index(int key, int n) {
	int i, low, high;

	// Ű ���� ����Ʈ ���� ���� ���� �ƴϸ� Ž�� ����
	if (key<list[0] || key>list[n - 1])
		return -1;

	// �ε��� ���̺��� �����Ͽ� �ش�Ű�� ���� ����
	for (i = 0; i < INDEX_SIZE; i++)
		if (index_list[i].key <= key && index_list[i + 1].key > key)
			break;
	if (i == INDEX_SIZE) {
		low = index_list[i - 1].index;
		high = n;
	}
	else {
		low = index_list[i].index;
		high = index_list[i + 1].index;
	}
	return seq_search(key, low, high);
}

int interpol_search(int key, int n) {
	int low, high, j;

	low = 0;
	high = n - 1;
	while ((list[high] >= key) && (key > list[low])) {
		j = ((float)(key - list[low]) / (list[high] - list[low]) * (high - low)) + low;
		if (key > list[j])low = j + 1;
		else if (key < list[j]) high = j - 1;
		else low = j;
	}
	if (list[low] == key)return(low);
	else return -1;
}