#include<stdio.h>
#include<stdlib.h>

// ���� �迭�� �̿��� ���� ����ü ����
typedef struct Stack {
	int* array;
	int top;
	int capacity;
}Stack;

// ���� �ʱ�ȭ �Լ�
Stack* createStack(int capacity) {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->capacity = capacity;
	stack->top = -1;
	stack->array = (int*)malloc(stack->capacity * sizeof(int));
	return stack;
}

// ������ ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(Stack* stack) {
	return stack->top == - 1;
}

// ������ ���� á���� Ȯ���ϴ� �Լ�
int isFull(Stack* stack) {
	return stack->top == stack->capacity - 1;
}

// ���ÿ� ���� �߰� �Լ�
void push(Stack* stack, int item) {
	if (isFull(stack)) {
		stack->capacity *= 2;	// ���� ũ�⸦ �� ��� Ȯ��
		stack->array = (int*)realloc(stack->array, stack->capacity * sizeof(int));
	}
	stack->array[++stack->top] = item;
}

// ���ÿ��� ���� ���� �Լ�
int pop(Stack* stack) {
	if (isEmpty(stack)) {
		fprintf(stderr,"ERROR: STACK IS EMPTY");
		return -1;	// Ư�� �� �Ǵ� ���� �ڵ带 ��ȯ�� �� �ֽ��ϴ�. 
	}
	return stack->array[stack->top];
}

// ������ �� �� ���� Ȯ�� �Լ�
int peek(Stack* stack) {
	if (isEmpty(stack)) {
		fprintf(stderr, "ERROR: STACK IS EMPTY");
		return -1;	// Ư�� �� �Ǵ� ���� �ڵ带 ��ȯ�� �� �ֽ��ϴ�. 
	}
	return stack->array[stack->top);
}

// ���� �޸� ���� �Լ�
void freeStack(Stack* stack) {
	free(stack->array);
	free(stack);
}

