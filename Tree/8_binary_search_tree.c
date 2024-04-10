#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
}TreeNode;

// 순환적인 탐색 함수
TreeNode* search(TreeNode* node, int key) {
	if (node == NULL)return NULL;
	if (key == node->key)return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

TreeNode* new_node(int item) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, int key) {
	// 트리가 공백이면 새로운 노드를 반환한다.
	if (node == NULL)return new_node(key);

	// 그렇지 않으면 순환적으로 트리를 내려간다. 
	if (key < node->key)
		node->left = insert_node(node->left, key);
	else if (key > node->key)
		node->right = insert_node(node->right, key);
	else if (key == node->key) {
		printf("삽입 실패 중복된 데이터 \n");
	}
	// 변경된 루트 포인터를 반환한다. 
	return node;
}

TreeNode* min_value_node(TreeNode* node) {
	TreeNode* current = node;

	// 맨 왼쪽 단말 노드를 찾으러 내려감
	while (current->left != NULL)
		current = current->left;

	return current;
}

// 이진 탐색 트리와 키가 주어지면 키가 저장된 노드를 삭제하고
// 새로운 루트 노드를 반환한다. 
TreeNode* delete_node(TreeNode* root, int key) {
	if (root == NULL)return root;

	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
	if (key < root->key)
		root->left = delete_node(root->left, key);
	// 만약 키가 루틉다 크면 오른쪽 서브 트리에 있는 것임
	else if (key > root->key)
		root->right = delete_node(root->right, key);
	// 키가 루트와 같으면 이 노드를 삭제하면 됨
	else {
		// 첫 번째나 두 번째 경우
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
		// 세 번째 경우
		TreeNode* temp = min_value_node(root->right);

		// 중위 순회시 후계 노드를 복사한다. 
		root->key = temp->key;
		// 중외 순회시 후계 노드를 삭제한다. 
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

// 중위 순회
void inorder(TreeNode* root) {
	if (root) {
		inorder(root->left);
		printf("[%d] ", root->key);
		inorder(root->right);
	}
}

// 노드의 개수를 구하는 함수
int get_node_count(TreeNode* node) {
	int count = 0;
	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);

	return count;
}

// 단말 노드 개수를 구하는 함수(조건문을 변경해 단말노드가 아닌 것의 개수도 구할 수 있음)
int get_leaf_count(TreeNode* node) {
	int count = 0;

	if (node != NULL) {
		if (node->left == NULL && node->right == NULL) {
			return 1;
		}
		else count = get_leaf_count(node->left) + get_leaf_count(node->right);
	}
	return count;
}

// 높이 구하기
int get_height(TreeNode* node) {
	int height = 0;

	if (node != NULL) {
		height = 1 + max(get_height(node->left), get_height(node->right));
	
		return height;
	}
}

int main() {
	TreeNode* root = NULL;
	TreeNode* temp = NULL;

	root = insert_node(root, 30);
	root = insert_node(root, 20);
	root = insert_node(root, 10);
	root = insert_node(root, 40);
	root = insert_node(root, 50);
	root = insert_node(root, 60);

	printf("이진 탐색 트리 중위 순회 결과 \n");
	inorder(root);
	printf("\n\n");
	if (search(root, 30) != NULL)
		printf("이진 탐색 트리에서 30을 발견함 \n");
	else
		printf("이진 탐색 트리에서 30을 발견못함\n");
	return 0;
}