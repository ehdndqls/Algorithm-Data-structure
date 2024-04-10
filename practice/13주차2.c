#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_WORD_LENGHT 50

typedef struct {
	char word[MAX_WORD_LENGHT];
	char meaning[MAX_WORD_LENGHT];
}element;

typedef struct AvlNode {
	element data;
	struct AvlNode* left_child, * right_child;
}AvlNode;

AvlNode* root;

AvlNode* rotate_LL(AvlNode* parent) {
	AvlNode* child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}

AvlNode* rotate_RR(AvlNode* parent) {
	AvlNode* child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}

AvlNode* rotate_LR(AvlNode* parent) {
	AvlNode* child = parent->left_child;
	parent->left_child = rotate_RR(child);
	return rotate_LL(parent);
}

AvlNode* rotate_RL(AvlNode* parent) {
	AvlNode* child = parent->right_child;
	parent->right_child = rotate_LL(child);
	return rotate_RR(parent);
}

int maxs(int a, int b) {
	int result;
	if (a > b) {
		result = a;
	}
	else if (a <= b) {
		result = b;
	}
	return result;
}

int get_height(AvlNode* node) {
	int height = 0;
	if (node != NULL)
		height = 1 + maxs(get_height(node->left_child), get_height(node->right_child));

	return height;
}

int get_height_diff(AvlNode* node) {
	if (node == NULL)
		return 0;

	return (get_height(node->left_child) - get_height(node->right_child));
}

AvlNode* rebalance(AvlNode** node) {
	int height_diff = get_height_diff(*node);

	if (height_diff > 1) { // height_deff = 2, 3, 4, ...
		if (get_height_diff((*node)->left_child) > 0)
			*node = rotate_LL(*node);
		else
			*node = rotate_LR(*node);
	}
	else if (height_diff < -1) { // height_deff = -2, -3, -4, ...
		if (get_height_diff((*node)->right_child) < 0)
			*node = rotate_RR(*node);
		else
			*node = rotate_RL(*node);
	}
	return *node;
}

AvlNode* avl_add(AvlNode** root, element new_key) {
	if (*root == NULL) {
		*root = (AvlNode*)malloc(sizeof(AvlNode));

		(*root)->data = new_key;
		(*root)->left_child = (*root)->right_child = NULL;
	}
	else if (strcmp(new_key.word, (*root)->data.word) > 0) {
		(*root)->left_child = avl_add(&((*root)->left_child), new_key);
		(*root) = rebalance(root);
	}
	else if (strcmp(new_key.word, (*root)->data.word) < 0) {
		(*root)->right_child = avl_add(&((*root)->right_child), new_key);
		(*root) = rebalance(root);
	}
	else {	// dupe
		printf("duplicated item\n");
		exit(1);
	}

	return *root;
}

AvlNode* avl_search(AvlNode* node, element key)
{
	if (node == NULL)
		return NULL;
	if (strcmp(key.word, node->data.word) == 0)
		return node;
	else if (strcmp(key.word,node->data.word) > 0)
		return avl_search(node->left_child, key);
	else
		return avl_search(node->right_child, key);

}
int main() {
	FILE* fp;
	char flag;
	element tmp;
	AvlNode *AN=NULL;

	fp = fopen("data14.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%c", &flag);

		if (flag == 'i') {
			fscanf(fp, "%s %s", tmp.word, tmp.meaning);
			printf("»ðÀÔ: %s %s\n", tmp.word, tmp.meaning);
			avl_add(&root,tmp);
		}
		else if (flag == 's') {
			fscanf(fp, "%s", tmp.word);
			strcpy(tmp.meaning, "");
			AN = avl_search(root, tmp);
			printf("%s - %s\n", AN->data.word, AN->data.meaning);
		}
	}	// end of while

	// display();
	fclose(fp);
	return 0;
}