#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 100

typedef int element;

typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
}TreeNode;

void preorder(TreeNode* root) {
	if (root) {
		printf("%d ", root->key);
		preorder(root->left);
		preorder(root->right);
	}
}

int MAX(int a, int b) {
	if (a >= b)
		return a;
	else
		return b;
}

void insertNode(TreeNode** root, element key) {
	TreeNode* t, * p;
	TreeNode* n;

	t = *root;
	p = NULL;

	while (t != NULL) {
	//이미 중복 데이터가 있음
		if (key == t->key)
			return;

		p = t;
		if (key < t->key)
			t = t->left;
		else
			t = t->right;
	}

	// while 루프가 끝난 시점은 중복데이터가 없고 마지막 단말노드까지 검색이 완료됐음
	//신규 트리 추가
	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL)
		return;
	n->key = key;
	n->left = n->right = NULL;

	if (p != NULL)
		if (key < p->key)
			p->left = n;
		else
			p->right = n;
	else
		*root = n;
}

int pow(int a) {
	int result = 1;
	for (int i = 0; i < a; i++)
		result *= 2;

	return result;
}

int get_height(TreeNode* root) {
	int height = 0;
	if (root != NULL)
		height = 1 + MAX(get_height(root->left), get_height(root->right));

	return height;
}


int get_leaf_count(TreeNode* root) {
	int count = 0;
	if (root != NULL)
		if (root->left == NULL && root->right == NULL)
			return 1;
		else
			count = get_leaf_count(root->left) + get_leaf_count(root->right);

	return count;
}


int main() {
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;
	element e;
	int tree_height;
	int leaf_node_count;
	FILE* fp;

	fopen_s(&fp, "data2.txt", "r");

	if (fp == NULL) {
		printf("파일을 열 수 없습니다. ");
		exit(1);
	}

	while (!feof(fp)) {
		fscanf(fp, " %d", &e);
		insertNode(&root, e);
		printf("insert %d\n",e);
	}
	preorder(root);

	tree_height = pow(get_height(root) - 1);
	leaf_node_count = get_leaf_count(root);

	if (tree_height == leaf_node_count)
		printf("완전 이진트리 입니다. \n");
	else
		printf("완전 이진트리가 아닙니다. \n");


	fclose(fp);
}