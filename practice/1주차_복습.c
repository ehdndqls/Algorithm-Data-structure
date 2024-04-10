/*rewind(stdin); //ǥ�� �Է� ���ۿ� �ִ� ��� ���� ����
scanf_s("%d %c %d", &a, %ch, 1, &b);
srand((unsigned)time(NULL));
size = sizeof(a) / sizeof(a[0]);//�Ҷ�� �ϰ����� ���� ��ȣ��� �̿� #define SIZE 10
�� rows �� cols
#define_CRT_SECURE_NO_WARNINGS
system("cls")//��µ� ȭ�� ����
8���� %o 16���� %x
char 1����Ʈ 
float 32��Ʈ
int 32��Ʈ
typedef enum {FALSE, TRUE } BOOL;
������  3.141592653589
printf �÷���(flag)  -��������, + �׻� ��ȣ���, 0 ��°� �տ� ���� ���� ��� 0���� ä���., blank(' ') ��°� �տ� ����� 0�� ��� ��ȣ ��� 0�� ä���., 8���� ��½ÿ��� 0�� ���̰� 16���� ��½� 0x�� ���δ�. 
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_NAME_SIZE 8

typedef struct Student {
	int studentNumber;
	char name[MAX_NAME_SIZE];
	int korean, english, math;
	int totalSum;
	double average;
}Student;

typedef struct ListNode {
	Student data;
	struct ListNode* link;
}ListNode;

ListNode* createNode(Student data) {
	ListNode* newNode;
	newNode = (ListNode*)malloc(sizeof(Student));
	newNode->data = data;
	newNode->link = NULL;

	return newNode;
}

void insertNode(ListNode** pHead, ListNode* newData) {
	//before: pHead
	//after: pHead -> newData ->NULL 
	if (*pHead == NULL) {//list enpty
		newData->link = NULL;
		*pHead = newData;
	}
	//before: pHead -> oldData -> NULL;
	//after: pHead -> newData -> oldData -> NULL;
	else {
		newData->link = *pHead;
		*pHead = newData;
	}
}

int deleteNode(ListNode* pHead) {
	if (pHead == NULL) {
		return 0;
	}
	else {
		ListNode* removedNode;
		removedNode = &pHead;
		*pHead = *pHead->link;
		free(pHead);
		deleteNode(&pHead);
	}
}

void display(ListNode* pHead) {
	ListNode* p = pHead;
	while (p != NULL) {
		printf("%d %s %d %d %d %d %f\n", p->data.studentNumber, p->data.name,
			p->data.korean, p->data.english, p->data.math, p->data.totalSum, p->data.average);
		p = p->link;
	}
}

void display2(ListNode* pHead) {
	ListNode* p = pHead;
	printf("|========================================|\n");
	printf("| ��    �� | ��  �� | ���� | ���� | ���� |\n");
	printf("|========================================|\n");
	while (p != NULL) {
		printf("| %5d | %5s | %3d  | %3d  | %3d  |\n", p->data.studentNumber,
			p->data.name, p->data.korean, p->data.english, p->data.math);
		//printf("%d %s %d %d %d %d %f\n", p->data.studentNumber, p->data.name, p->data.korean, p->data.english, p->data.math, p->data.totalSum, p->data.average);
		p = p->link;
	}
	printf("|========================================|\n");
}

ListNode* search(ListNode* pHead, int sNo) {
	ListNode* p = pHead;

	while (p != NULL) {
		if (p->data.studentNumber == sNo) {// �˻� ����
			return p;
		}
		else
			p = p->link;
	}

	return NULL;
}

int main() {
	//1.������ ������ �����ؼ� ������ ���� ���Ë����� �ݺ�
	FILE* fp;
	Student tmp;
	ListNode* head = NULL;

	fopen_s(&fp, "data.txt", "r");
	if (fp == NULL) {
		printf("file not found\n");
		exit(0);
	}

	while (!feof(fp)) {
		//1-1. �ӽñ���ü ������ ���Ͽ��� ���� ���� ����
		fscanf(fp, "%d %s %d %d %d", &tmp.studentNumber, tmp.name, &tmp.korean, &tmp.english, &tmp.math);

		//1-2 �հ�� ����� ����ؼ� �ӽñ���ü�� ����
		tmp.totalSum = tmp.korean + tmp.english + tmp.math;
		tmp.average = tmp.totalSum / 3;

		//2. �ӽñ���ü ũ�⸸ŭ �������� �޸𸮸� �Ҵ�
		//3. ���Ḯ��Ʈ �Լ����� �����ؼ� ���� �߰��Ѵ�.
		insertNode(&head, createNode(tmp));
	}


	//4.���Ḯ��Ʈ�� �����ؼ� ����Ʈ ��带 �ϳ��� ���
	display(head);

	//2�� ����
	// 1. ��ɾ� ȭ�� ���
	// 2. ����� ��� �Է�(�߰�, ���, ����, �˻� i, d, s,q)
	// 3. switch �б� ��ƾ �߰� case "i"
	// 4. �Է� i ����� ���, �й�, �̸�, ����, ����, ���� ���� �Է� �޾Ƽ� ����ü�� ����
	// 5. ���� ��ƾ�� ���Ͽ��� ������ �о ���Ḯ��Ʈ�� �����ϴ� �κа� ����

	int command=-1;
	int sNo;

	while (command!=0) {
		printf("<<���� ���� ���α׷�>>\n>> -0- ����\n>> -1- �˻�\n>> -2- ���\n>> -3- �߰�\n\n");
		scanf_s("%d", &command);

		switch (command) {
		case 3:
			printf("�߰��� �л� �̸�: ");
			scanf_s("%s", tmp.name, 20);
			printf("�й�: ");
			scanf_s("%d", &tmp.studentNumber);
			printf("���� ����: ");
			scanf_s("%d", &tmp.korean);
			printf("���� ����: ");
			scanf_s("%d", &tmp.english);
			printf("���� ����: ");
			scanf_s("%d", &tmp.math);
			tmp.totalSum = tmp.korean + tmp.english + tmp.math;
			tmp.average = tmp.totalSum / 3;
			insertNode(&head, createNode(tmp));
			break;
		case 2:
			display2(head);
			break;
		case 1:
			printf("�˻��� �й�: ");
			scanf_s("%d", &sNo);
			ListNode* searchResult = search(head, sNo);
			printf("<�̸�: %s>\n<����: %d>\n<����: %d>\n<����: %d>\n<����: %d>\n", searchResult->data.name, searchResult->data.korean, searchResult->data.english, searchResult->data.math, searchResult->data.totalSum);
			break;
		case 0:
			break;
		default:
			break;
		}
	}

	//5. �����ִ� ������ �ݾ��ش�. �޸𸮵� �������ش�.
	deleteNode(&head);
	fclose(fp);

}