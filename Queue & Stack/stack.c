#include<stdio.h>
#include<stdlib.h>

// 동적 배열을 이용한 스택 구조체 정의
typedef struct Stack {
	int* array;
	int top;
	int capacity;
}Stack;

// 스택 초기화 함수
Stack* createStack(int capacity) {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->capacity = capacity;
	stack->top = -1;
	stack->array = (int*)malloc(stack->capacity * sizeof(int));
	return stack;
}

// 스택이 비어있는지 확인하는 함수
int isEmpty(Stack* stack) {
	return stack->top == - 1;
}

// 스택이 가득 찼는지 확인하는 함수
int isFull(Stack* stack) {
	return stack->top == stack->capacity - 1;
}

// 스택에 원소 추가 함수
void push(Stack* stack, int item) {
	if (isFull(stack)) {
		stack->capacity *= 2;	// 스택 크기를 두 배로 확장
		stack->array = (int*)realloc(stack->array, stack->capacity * sizeof(int));
	}
	stack->array[++stack->top] = item;
}

// 스택에서 원소 제거 함수
int pop(Stack* stack) {
	if (isEmpty(stack)) {
		fprintf(stderr,"ERROR: STACK IS EMPTY");
		return -1;	// 특정 값 또는 오류 코드를 반환할 수 있습니다. 
	}
	return stack->array[stack->top];
}

// 스택의 맨 위 원소 확인 함수
int peek(Stack* stack) {
	if (isEmpty(stack)) {
		fprintf(stderr, "ERROR: STACK IS EMPTY");
		return -1;	// 특정 값 또는 오류 코드를 반환할 수 있습니다. 
	}
	return stack->array[stack->top);
}

// 스택 메모리 해제 함수
void freeStack(Stack* stack) {
	free(stack->array);
	free(stack);
}

