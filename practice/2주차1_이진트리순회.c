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

void inorder(TreeNode* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("[%d] ", root->data);
		inorder(root->right);
	}
}
void preorder(TreeNode* root) {
	if (root != NULL) {
		printf("[%d] ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}
void postorder(TreeNode* root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("[%d] ", root->data);
	}
}
int main() {
	printf("������ȸ: ");
	inorder(root);
	printf("\n");

	printf("������ȸ: ");
	preorder(root);
	printf("\n");

	printf("������ȸ: ");
	postorder(root);
	printf("\n");
}