#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 100

typedef struct element {
	char word[MAX_WORD_SIZE];
	char meaning[MAX_WORD_SIZE];
}element;

typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
}TreeNode;

int compare(element e1, element e2) {
	return strcmp(e1.word, e2.word); //e1이 e2보다 사전적으로 앞이면 양수
}

void insertNode(TreeNode** root, element key) {
	TreeNode* t, * p;
	TreeNode* n;

	t = *root;
	p = NULL;

	while (t != NULL) {
		if (compare(key, t->key) == 0) //이미 중복 데이터가 있음
			return;

		p = t;           // 이전 노드를 저장
		if (compare(key, t->key) < 0)  // t->key 가 사전적으로 앞이면
			t = t->left;
		else
			t = t->right;              // key가 사전적으로 앞이면
	}

	// while 루프가 끝난 시점은 중복데이터가 없고 마지막 단말노드까지 검색이 완료됐음
	//신규 트리 추가
	n = (TreeNode*)malloc(sizeof(TreeNode)); //신규노드 생성, 초기화
	if (n == NULL)
		return;
	n->key = key;
	n->left = n->right = NULL;

	if (p != NULL)
		if (compare(key, p->key) < 0)   // p-key가 사전적으로 앞이면 왼쪽
			p->left = n;
		else
			p->right = n;
	else
		*root = n;
}

void deleteNode(TreeNode** root, element key) {

	TreeNode* t, * p, * child, * succ, * succ_p; 
	// t = traverse node 
	// p = parent node of t

	p = NULL;
	t = *root;

	while (t != NULL && compare(t->key, key) != 0) {
		// key값이 일치하지 않는다.
		p = t;
		t = (compare(key, t->key) < 0) ? t->left : t->right;
	}

	//case 1 t == NULL 검색실패, 삭제하려는 key은 존재하지 않는다. 
	if (t == NULL) {
		printf("삭제하려는 데이터가 없습니다 \n");
		return;
	}

	// case 2 key가 트리에 존재하는 경우  
	// case 2-1 t의 child node 가 없는 경우 (leaf node)
	if ((t->left == NULL) && (t->right == NULL)) {
		// case 2-1-1 parent node가 있는 경우
		if (p != NULL) {
			// case 2-1-1-1 t가 p의 왼쪽 child인 경우
			if (p->left == t)
				p->left = NULL;
			// case 2-1-1-2 가 p의 오른쪽 child인 경우
			else
				p->right = NULL;
		}
		// case 2-1-2 parent node 가 없는 경우 -> 트리에 유일한 노드가 t인 경우
		else {
			*root = NULL;
		}
	}

	// case 2-2 t의 child node가 한개만 있는 경우
	else if ((t->left == NULL) || (t->right == NULL)) {
		// 손주 노드의 포인터를 얻는다. 
		child = (t->left != NULL) ? t->left : t->right;

		// case 2-2-1 parent node가 있는 경우
		if (p != NULL) {
			// case 2-2-1-1 t가 parent의 왼쪽 자식인 경우
			if (p->left == t)
				p->left = child;
			// case 2-2-1-2 t가 parent의 오른족 자식인 경우
			else
				p->right = child;
		}
		// case 2-2-2 parent node가 없는 경우
		else
			*root = child;
	}

	// case 2-3 t의 left, right node가 모두 존재하는 경우
	else {
		// 오른쪽 서브트리에서 후계자를 선정
		succ_p = t;
		succ = t->right;

		// 오른쪽 서브트리에서 가장 작은 노드를 찾자
		// 오른쪽 서브트리에서 가장 작은 값은 가장 왼쪽 끝에 있는 노드다
		// 이진 탐색 트리이기 때문에 가능한 조건
		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}

		if (succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;

		t->key = succ->key;
		t = succ;
	}

	free(t);               //                                                                   
}

TreeNode* searchNode(TreeNode* root, element key) {
	TreeNode* p = root;

	while (p != NULL) {
		switch (compare(key, p->key)) {
		case 0:
			return p;
		case -1:
			p = p->left;
			break;
		case 1:
			p = p->right;
			break;
		} // end of switch
	} // end of while
	//while 문 밖에 나오면 무슨일이 생긴 것인가?
	return p; //이때p는 NULL
}

TreeNode* printNode(TreeNode* root) { // 정렬 상태로 출력하기 위해서 inorder 구현
	if (root != NULL) {
		//L V R
		printNode(root->left);
		printf("트리노드 (%s:%s)", root->key.word, root->key.meaning);
		printNode(root->right);
		printf(" -> ");
	}
}

int main() {
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;
	element e;
	FILE* fp;

	fopen_s(&fp, "data.txt", "r");

	if (fp == NULL) {
		printf("파일을 열 수 없습니다. ");
		exit(1);
	}

	element buf;
	char command;
	while (!feof(fp)) {
		fscanf(fp, " %c", &command);
		switch (command) {
		case 'i':
			fscanf(fp, " %s %s", buf.word, buf.meaning);
			insertNode(&root, buf);
			printf("%s : %s 삽입\n", buf.word, buf.meaning);
			break;
		case 'd':
			fscanf(fp, " %s", e.word);
			strcpy(e.meaning, "");
			deleteNode(&root, e);
			printf("단어 %s 삭제 완료\n", e.word);
			break;
		case 's':
			fscanf(fp, " %s", e.word);
			tmp = searchNode(root, e);
			if (tmp != NULL) {
				printf("\n단어 %s의 의미는 %s입니다.\n", tmp->key.word, tmp->key.meaning);
			}
			else {
				printf("\n단어 %s는 사전에 없습니다. \n", e.word);
			}
			break;
		case 'p':
			printf("\n");
			printNode(root);
			printf("\n");
			break;
		case 'q':
			fclose(fp);
			exit(1);
		}
	}
}