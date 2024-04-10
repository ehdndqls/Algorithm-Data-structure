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
	while (tmp != NULL) {
		printf("%d->", tmp->data);
		tmp = tmp->link;
	}
	printf("NULL \n");
}

ListNode* concat_list(ListNode* head1, ListNode* head2) {
	if (head1 == NULL)
		return head2;
	else if (head2 == NULL)
		return head1;
	else {
		ListNode* p;
		p = head1;
		while (p->link != NULL) 
			p = p->link;
		p->link = head2;
		return head1;
	}
}

int main() {
	ListNode* head1 = NULL;
	ListNode* head2 = NULL;
	ListNode* head = NULL;
	head1 = insert_first(head1, 10);
	head1 = insert_first(head1, 20);
	head1 = insert_first(head1, 30);
	print_list(head1);
	head2 = insert_first(head2, 40);
	head2 = insert_first(head2, 50);
	print_list(head2);
	
	head = concat_list(head1, head2);
	print_list(head);
	
	while (head != NULL)
		head = delete_first(head);

	return 0;
}