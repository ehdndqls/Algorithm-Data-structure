#include<stdio.h>
#include<stdlib.h>

Queue* createQueue(int capacity); //  ���� ť �ʱ�ȭ �Լ�
int isFull(Queue* queue); // ť�� ���� á���� Ȯ���ϴ� �Լ�
int isEmpty(Queue* queue); // ť�� ����ִ��� Ȯ���ϴ� �Լ�
void enqueue(Queue* queue, element item); // ť�� ��� �߰� �Լ�
int dequeue(Queue* queue); // ť���� ��� ���� �Լ�
int front(Queue* queue); // ť�� �� �� ��� Ȯ�� �Լ�
int rear(Queue* queue); // ť�� �� �� ��� Ȯ�� �Լ�
void freeQueue(Queue* queue); // ť �޸� ���� �Լ�


typedef int element;

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

