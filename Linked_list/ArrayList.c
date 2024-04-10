#include<stdio.h>
#include<stdlib.h>
#define MAX_LIST_SIZE 100

typedef int element;

typedef struct {
	element array[MAX_LIST_SIZE];
	int size;
}ArrayListType;

void error(char * message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init(ArrayListType* list) {
	list->size = 0;
}

int is_empty(ArrayListType* list) {
	return list->size == 0;
}

int is_full(ArrayListType* list) {
	return list->size >= MAX_LIST_SIZE;
}

element get_entry(ArrayListType* list, int pos) {
	if (pos < 0 || pos >= MAX_LIST_SIZE)
		error("위치오류");
	return list->array[pos];
}
void print_list(ArrayListType* list) {
	int i;
	for (i = 0; i < list->size; i++) 
		printf("%d->", list->array[i]);
	printf("\n");
}

void insert_last(ArrayListType* list, element item) {
	if (is_empty(&list)) {
		error("overflow");
	}
	list->array[list->size++] = item;
}

void insert(ArrayListType* list, int pos, element item) {
	
	if (is_empty(&list))
		error("overflow");
	else if (pos < 0 || pos > list->size)
		error("incorrect location");
	else if (pos == list->size) {
		insert_last(list, item);
		return;
	}

	for (int i = (list->size-1); i >=pos ; i--) 
		list->array[i + 1] = list->array[i];

	list->array[pos] = item;
	list->size++;
}

element delete(ArrayListType* list, int pos) {
	element item;

	if (pos < 0 || pos >= list->size)
		error("incorrect location");

	item = list->array[pos];

	for (int i = pos; i < list->size - 1; i++)
		list->array[pos] = list->array[pos + 1];

	list->size--;

	return item;
}

int main() {
	ArrayListType list;

	init(&list);
	insert(&list, 0, 10); print_list(&list);
	insert(&list, 0, 20); print_list(&list);
	insert(&list, 0, 30); print_list(&list);
	insert_last(&list, 40); print_list(&list);
	delete(&list, 0); print_list(&list);
	
	return 0;
}