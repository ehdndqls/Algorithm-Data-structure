#include<stdio.h>
#include<stdlib.h>

Queue* createQueue(int capacity); //  원형 큐 초기화 함수
int isFull(Queue* queue); // 큐가 가득 찼는지 확인하는 함수
int isEmpty(Queue* queue); // 큐가 비어있는지 확인하는 함수
void enqueue(Queue* queue, element item); // 큐에 요소 추가 함수
int dequeue(Queue* queue); // 큐에서 요소 제거 함수
int front(Queue* queue); // 큐의 맨 앞 요소 확인 함수
int rear(Queue* queue); // 큐의 맨 뒤 요소 확인 함수
void freeQueue(Queue* queue); // 큐 메모리 해제 함수


typedef int element;

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

