#include<stdio.h>
#include<stdlib.h>

typedef struct {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

TreeNode n1 = { 5,NULL,NULL };
TreeNode n2 = { 22,NULL,NULL };
TreeNode n3 = { 95,NULL,NULL };
TreeNode n4 = { 15,&n1,NULL };
TreeNode n5 = { 35,&n2,NULL };
TreeNode n6 = { 93,&n5,&n3 };
TreeNode n7 = { 17,&n4,&n6 };
TreeNode* root = &n7;

#define MAX_STACK_SIZE 100

TreeNode* stack[MAX_STACK_SIZE];
int top = -1;

void push(TreeNode* p) {
	if (top < MAX_STACK_SIZE - 1)
		stack[++top] = p;
}

TreeNode* pop() {
	TreeNode* p = NULL;
	if (top >= 0)
		p = stack[top--];
	return p;
}

void iterative_inorder(TreeNode* p) {
	while (1) {
		for (; root; root = root->left)
			push(root);
		root = pop();
		if (!root)
			break;

		printf("[%d] ", root->data);

		root = root->right;
	}
}

int main() {
	printf("반복 중위 순회: ");
	iterative_inorder(root);
	printf("\n");
	return 0;
}