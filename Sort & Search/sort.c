#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_SIZE 10
#define SWAP(x,y,t) ( (t)=(x), (x)=(y), (y)=(t) )

//int list[MAX_SIZE];
int n;

void selection_sort(int list[], int n) {
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) // �ּҰ� Ž��		
			if (list[j] < list[least]) least = j;		// �������� > �ιٲٱ�
		SWAP(list[i], list[least], temp);
	}
}

void insert_sort(int list[], int n) {
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--)			//�������� list[j] < key �ιٲٱ�
			list[j + 1] = list[j];	// ���ڵ��� ������ �̵�
		list[j + 1] = key;
	}
}

void bubble_sort(int list[], int n) {
	int i, j, temp;
	for (i = n - 1; i > 0; i--){
		for (j = 0; j < i; j++)
			if (list[j] > list[j + 1])			// �������� < �� �ٲٱ�
				SWAP(list[j], list[j + 1], temp);
		}
}

// gap ��ŭ ������ ��ҵ��� ���� ����
// ������ ������ first���� last
void inc_insertion_sort(int list[], int first, int last, int gap) {
	int i, j, key;
	for (i = first + gap; i > last; i = i + gap){
		key = list[i];
		for (j = i - gap; j >= first && list[j] > key; j = j - gap)
			list[j + gap] = list[j];	// ���ڵ��� ������ �̵�
		list[j + gap] = key;
	}
}


void shell_sort(int list[], int n) { // n=size
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2){
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)	// �κ� ����Ʈ�� ������ gap
			inc_insertion_sort(list, i, n - 1, gap);
	}
}


int sorted[MAX_SIZE];

/* i�� ���ĵ� ���� ����Ʈ�� ���� �ε���
   j�� ���ĵ� ������ ����Ʈ�� ���� �ε���
   k�� ���ĵ� ����Ʈ�� ���� �ε��� */

void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	// ���� ���ĵ� list�� �պ�
	while (i <= mid && j <= right) {
		if (list[i] <= list[j])					// �������� �̰� �ε�ȣ ���� ���� >=��
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	if (i > mid) // ���� �ִ� ���ڵ��� �ϰ� ����
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else         // ���� �ִ� ���ڵ��� �ϰ� ����
		for (l = i; l <= right; l++)
			sorted[k++] = list[l];
   // �迭 sorted[]�� ����Ʈ�� �迭 list[]�� �纹��
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;			// ����Ʈ�� �յ� ����
		merge_sort(list, left, mid);		// �κ� ����Ʈ ����
		merge_sort(list, mid + 1, right);	// �κ� ����Ʈ ����
		merge(list, left, mid, right);		// �պ�
	}
}

int partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];
	do {
		do
			low++;
		while (list[low] < pivot);		
		do
			high--;
		while (list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], temp);
	} while (low < high);

	SWAP(list[left], list[high], temp);
	return high;
}

void quick_sort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

// --------------------ť �ڵ� -------------------------
typedef int element;
element list[MAX_SIZE];

// ���� ť ����ü ����
typedef struct Queue {
	element* array;
	int front, rear, size, capacity;
}Queue;

// ���� ť �ʱ�ȭ �Լ�
Queue* createQueue(int capacity) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->capacity = capacity;
	queue->front = queue->size = 0;
	queue->rear = capacity - 1;	// rear�� -1�� �ʱ�ȭ�Ͽ� ù ��° ��Ҹ� ������ �� ������ ��ġ�� ����
	queue->array = (element*)malloc(queue->capacity * sizeof(element));
	return queue;
}

// ť�� ���� á���� Ȯ���ϴ� �Լ�
int isFull(Queue* queue) {
	return (queue->size == queue->capacity);
}

// ť�� ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(Queue* queue) {
	return (queue->size == 0);
}

// ť�� ��� �߰� �Լ�
void enqueue(Queue* queue, element item) {
	if (isFull(queue)) {
		fprintf(stderr, "ERROR: QUEUE IS FULL.");
		return;
	}
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->array[queue->rear] = item;
	queue->size = queue->size + 1;
}

// ť���� ��� ���� �Լ�
int dequeue(Queue* queue) {
	if (isEmpty(queue)) {
		fprintf(stderr, "ERROR: QUEUE IS EMPTY");
		return -1; // Ư�� �� �Ǵ� ���� �ڵ带 ��ȯ�� �� �ֽ��ϴ�. 
	}
	element item = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size = queue->size - 1;
	return item;
}

// ť�� �� �� ��� Ȯ�� �Լ�
int front(Queue* queue) {
	if (isEmpty(queue)) {
		fprintf(stderr, "ERROR: QUEUE IS EMPTY");
		return -1; // Ư�� �� �Ǵ� ���� �ڵ带 ��ȯ�� �� �ֽ��ϴ�. 
	}
	return queue->array[queue->front];
}

// ť�� �� �� ��� Ȯ�� �Լ�
int rear(Queue* queue) {
	if (isEmpty(queue)) {
		fprintf(stderr, "ERROR: QUEUE IS EMPTY");
		return -1; // Ư�� �� �Ǵ� ���� �ڵ带 ��ȯ�� �� �ֽ��ϴ�. 
	}
	return queue->array[queue->rear];
}

// ť �޸� ���� �Լ�
void freeQueue(Queue* queue) {
		free(queue->array);
		free(queue);
}

//----------------------------------��������� ť--------------

#define BUCKETS 10	// 10������ ����� ���� 0~9 �� 10
#define DIGITS 2	// �ڸ���
void radix_sort(int list[], int n) {
	int i, b, d, factor = 1;
	Queue* queues[BUCKETS];
	
	for (b = 0; b < BUCKETS; b++) 
		queues[b] = createQueue(100);
		
	for (d = 0; d < DIGITS; d++) {
		for (i = 0;i < n; i++)
			enqueue(queues[(list[i] / factor) % 10], list[i]);

		for (b = i = 0; b < BUCKETS; b++)
			while (!isEmpty(queues[b]))
				list[i++] = dequeue(queues[b]);
		factor *= 10;
	}
	for (int i = 0; i < BUCKETS; i++) {
		freeQueue(queues[i]);
	}
}

int main() {
	int i;
	n = MAX_SIZE;
	srand((unsigned)time(NULL));
	for (i = 0; i < n; i++)
		list[i] = rand() % 100;

	radix_sort(list, n);
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
	return 0;
}