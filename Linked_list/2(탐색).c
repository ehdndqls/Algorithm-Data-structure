#include<stdio.h>
#include<stdlib.h>

typedef int element;

typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListNode* insert_first(ListNode* head, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

ListNode* insert(ListNode* head, ListNode* pre, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}

ListNode* delete_first(ListNode* head) {
	ListNode* removed;
	if (head == NULL)
		return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete(ListNode* head, ListNode* pre) {
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

void print_list(ListNode* head) {
	ListNode* tmp = head;
	while (tmp->link != NULL) {
		printf("%d->", tmp->data);
		tmp = tmp->link;
	}
	printf("NULL \n");
}

ListNode* search_list(ListNode* head, element key) {
	ListNode* p = head;

	while (p != NULL) {
		if (p->data == key)
			return p;
		p = p->link;
	}
	return NULL;
}

int main() {
	ListNode* head = NULL;

	head = insert_first(head, 10);
	print_list(head);
	head = insert_first(head, 20);
	print_list(head);
	head = insert_first(head, 30);
	print_list(head);

	if (search_list(head, 30) != NULL)
		printf("리스트에서 3을 찾았습니다. \n");
	else
		printf("리스트에서 3을 찾지 못했습니다. \n");

	while (head != NULL) {
		head = delete_first(head);
	}

	return 0;
}