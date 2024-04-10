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
		for (j = i + 1; j < n; j++) // 최소값 탐색		
			if (list[j] < list[least]) least = j;		// 내림차순 > 로바꾸기
		SWAP(list[i], list[least], temp);
	}
}

void insert_sort(int list[], int n) {
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--)			//내림차순 list[j] < key 로바꾸기
			list[j + 1] = list[j];	// 레코드의 오른쪽 이동
		list[j + 1] = key;
	}
}

void bubble_sort(int list[], int n) {
	int i, j, temp;
	for (i = n - 1; i > 0; i--){
		for (j = 0; j < i; j++)
			if (list[j] > list[j + 1])			// 내림차순 < 로 바꾸기
				SWAP(list[j], list[j + 1], temp);
		}
}

// gap 만큼 떨어진 요소들을 삽입 정렬
// 정렬의 범위는 first에서 last
void inc_insertion_sort(int list[], int first, int last, int gap) {
	int i, j, key;
	for (i = first + gap; i > last; i = i + gap){
		key = list[i];
		for (j = i - gap; j >= first && list[j] > key; j = j - gap)
			list[j + gap] = list[j];	// 레코드의 오른쪽 이동
		list[j + gap] = key;
	}
}


void shell_sort(int list[], int n) { // n=size
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2){
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)	// 부분 리스트의 개수는 gap
			inc_insertion_sort(list, i, n - 1, gap);
	}
}


int sorted[MAX_SIZE];

/* i는 정렬된 왼쪽 리스트에 대한 인덱스
   j는 정렬된 오른쪽 리스트에 대한 인덱스
   k는 정렬될 리스트에 대한 인덱스 */

void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	// 분할 정렬된 list의 합병
	while (i <= mid && j <= right) {
		if (list[i] <= list[j])					// 내림차순 이거 부등호 방향 변경 >=로
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	if (i > mid) // 남아 있는 레코드의 일괄 복사
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else         // 남아 있는 레코드의 일괄 복사
		for (l = i; l <= right; l++)
			sorted[k++] = list[l];
   // 배열 sorted[]의 리스트를 배열 list[]로 재복사
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;			// 리스트의 균등 분할
		merge_sort(list, left, mid);		// 부분 리스트 정렬
		merge_sort(list, mid + 1, right);	// 부분 리스트 정렬
		merge(list, left, mid, right);		// 합병
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

// --------------------큐 코드 -------------------------
typedef int element;
element list[MAX_SIZE];

// 원형 큐 구조체 정의
typedef struct Queue {
	element* array;
	int front, rear, size, capacity;
}Queue;

// 원형 큐 초기화 함수
Queue* createQueue(int capacity) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->capacity = capacity;
	queue->front = queue->size = 0;
	queue->rear = capacity - 1;	// rear를 -1로 초기화하여 첫 번째 요소를 삽입할 때 적절한 위치로 설정
	queue->array = (element*)malloc(queue->capacity * sizeof(element));
	return queue;
}

// 큐가 가득 찼는지 확인하는 함수
int isFull(Queue* queue) {
	return (queue->size == queue->capacity);
}

// 큐가 비어있는지 확인하는 함수
int isEmpty(Queue* queue) {
	return (queue->size == 0);
}

// 큐에 요소 추가 함수
void enqueue(Queue* queue, element item) {
	if (isFull(queue)) {
		fprintf(stderr, "ERROR: QUEUE IS FULL.");
		return;
	}
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->array[queue->rear] = item;
	queue->size = queue->size + 1;
}

// 큐에서 요소 제거 함수
int dequeue(Queue* queue) {
	if (isEmpty(queue)) {
		fprintf(stderr, "ERROR: QUEUE IS EMPTY");
		return -1; // 특정 값 또는 오류 코드를 반환할 수 있습니다. 
	}
	element item = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size = queue->size - 1;
	return item;
}

// 큐의 맨 앞 요소 확인 함수
int front(Queue* queue) {
	if (isEmpty(queue)) {
		fprintf(stderr, "ERROR: QUEUE IS EMPTY");
		return -1; // 특정 값 또는 오류 코드를 반환할 수 있습니다. 
	}
	return queue->array[queue->front];
}

// 큐의 맨 뒤 요소 확인 함수
int rear(Queue* queue) {
	if (isEmpty(queue)) {
		fprintf(stderr, "ERROR: QUEUE IS EMPTY");
		return -1; // 특정 값 또는 오류 코드를 반환할 수 있습니다. 
	}
	return queue->array[queue->rear];
}

// 큐 메모리 해제 함수
void freeQueue(Queue* queue) {
		free(queue->array);
		free(queue);
}

//----------------------------------여기까지가 큐--------------

#define BUCKETS 10	// 10진수는 경우의 수가 0~9 즉 10
#define DIGITS 2	// 자리수
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