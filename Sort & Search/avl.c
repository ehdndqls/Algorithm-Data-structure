#include<stdio.h>
#include<stdlib.h>
#define MAX(a,b) ((a) > (b) ? (a) : (b))

// 트리 노드 정의
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

// 트리의 높이를 반환
int getHeight(TreeNode* node) {
	int height = 0;
	if (node != NULL)
		height = 1 + MAX(getHeight(node->left), getHeight(node->right));

	return height;
}

// 노드의 균형인수를 반환
int getBalance(TreeNode* node) {
	if (node == NULL) return 0;

	return getHeight(node->left) - getHeight(node->right);
}

// 노드를 동적으로 생성하는 함수
TreeNode* createNode(int item) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->data = item;
	node->left = node->right = NULL;
	return (node);
}

TreeNode* rotate_LL(TreeNode* parent) {
	TreeNode* child = parent->left;
	parent->left = child->right;
	child->right = parent;
	return child;
}

TreeNode* rotate_RR(TreeNode* parent) {
	TreeNode* child = parent->right;
	parent->right = child->left;
	child->left = parent;
	return child;
}

TreeNode* rotate_LR(TreeNode* parent) {
	TreeNode* child = parent->left;
	parent->left = rotate_RR(child);
	return rotate_LL(parent);
}

TreeNode* rotate_RL(TreeNode* parent) {
	TreeNode* child = parent->right;
	parent->right = rotate_LL(child);
	return rotate_RR(parent);
}

TreeNode* rebalance(TreeNode* node) {
	int balance = getBalance(node);

	if (balance > 1) {
		if (getBalance(node->left)>0)
			node = rotate_LL(node);
		else
			node = rotate_LR(node);
	}
	else if (balance < -1) {
		if (getBalance(node->right)<0)
			node = rotate_RR(node);
		else
			node = rotate_RL(node);
	}
	return node;
}

TreeNode* avl_add(TreeNode* root, int item) {
	if (root == NULL)
		root = createNode(item);
	else if (item < root->data) {
		root->left = avl_add(root->left, item);
		root = rebalance(root);
	}
	else if (item > root->data) {
		root->right = avl_add(root->right, item);
		root = rebalance(root);
	}
	else {
		fprintf(stderr, "duplicated item");
		exit(1);
	}

	return root;
}

TreeNode* searchNode(TreeNode* root, int key) {
	if (root == NULL)
		return NULL;
	if (key == root->data)
		return root;
	else if (key < root->data)
		return searchNode(root->left, key);
	else if (key > root->data)
		return searchNode(root->right, key);
}

void display(TreeNode* root) {
	if (root != NULL) {
		printf("[%d] ", root->data);
		display(root->left);
		display(root->right);
	}
}

void freeTree(TreeNode* root) {
	if (root != NULL) {
		freeTree(root->left);    // 왼쪽 서브트리 해제
		freeTree(root->right);   // 오른쪽 서브트리 해제
		free(root);              // 현재 노드 해제
	}
}

int main() {
	TreeNode* root = NULL;

	root = avl_add(root, 1);
	root = avl_add(root, 4);
	root = avl_add(root, 2);
	root = avl_add(root, 5);
	root = avl_add(root, 6);
	root = avl_add(root, 3);

	printf("전위 순회 결과 \n");
	display(root);

	freeTree(root);

	return 0;
}
