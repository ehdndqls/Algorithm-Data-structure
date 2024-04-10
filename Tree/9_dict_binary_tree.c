#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 200

// ������ ����
typedef struct {
	char word[MAX_WORD_SIZE];	// Ű�ʵ�
	char meaning[MAX_MEANING_SIZE];
}element;
// ����� ����
typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
}TreeNode;

// ���� e1 < e2 �̸� -1 ��ȯ
// ���� e1 == e2 �̸� 0 ��ȯ
// ���� e1 > e2 �̸� 1 ��ȯ
int compare(element e1, element e2) {
	return strcmp(e1.word, e2.word);
}

void display(TreeNode* p) {
	if (p != NULL) {
		printf("(");
		display(p->left);
		printf("%s:%s", p->key.word, p->key.meaning);
		display(p->right);
		printf(")");
	}
}

TreeNode* new_node(element item) {
	TreeNode* n = (TreeNode*)malloc(sizeof(TreeNode));
	n->key = item;
	n->left = n->right = NULL;
	return n;
}

TreeNode*	insert_node(TreeNode* root, element key) {
	if (root == NULL)
		return new_node(key);
	if (compare(root->key, key) > 0)
		root->right = insert_node(root->right, key);
	else if (compare(root->key, key) < 0)
		root->left = insert_node(root->left, key);
	return root;
}

TreeNode* search_node(TreeNode* root, element key) {
	TreeNode* p = root;
	while (p != NULL) {
		if (compare(key, p->key) == 0)
			return root;
		else if (compare(key, p->key) > 0)
			p = p->right;
		else if (compare(key, p->key) < 0)
			p = p->left;
	}
	return p;
}

TreeNode* min_value_node(TreeNode* node) {
	TreeNode* current = node;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

TreeNode* delete_node(TreeNode* root, element key) {
	if (root == NULL)return root;
	if (compare(key, root->key) < 0)
		root->left = delete_node(root->left, key);
	else if (compare(key, root->key) > 0)
		root->right = delete_node(root->right, key);
	else {
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		TreeNode* temp = min_value_node(root->right);
		root->key = temp->key;
		root->right = delete_node(root->right, key);
	}
	return root;
}

void help() {
	printf("**** i: �Է�, d: ����, s: Ž��, p: ���, q: ���� ****: ");
}
int main() {
	char command;
	element e;
	TreeNode* root = NULL;
	TreeNode* tmp;

	do {
		help();
		command = getchar();
		rewind(stdin);
		switch (command) {
		case 'i':
			printf("�ܾ�: ");
			scanf("%s", e.word);
			printf("�ǹ�: ");
			scanf("%s", e.meaning);
			root = insert_node(root, e);
			break;
		case 'd':
			printf("�ܾ�: ");
			scanf("%s", e.word);
			root = delete_node(root,e);
			break;
		case 's':
			printf("�ܾ�: ");
			scanf("%s", e.word);
			tmp = search_node(root, e);
			if (tmp != NULL)
				printf("�ǹ�: %s\n", tmp->key.meaning);
			break;
		case 'p':
			display(root);
			printf("\n");
			break;
		}
	} while (command != 'q');
	return 0;
}