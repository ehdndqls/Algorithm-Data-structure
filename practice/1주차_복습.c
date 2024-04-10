/*rewind(stdin); //표준 입력 버퍼에 있는 모든 문자 제거
scanf_s("%d %c %d", &a, %ch, 1, &b);
srand((unsigned)time(NULL));
size = sizeof(a) / sizeof(a[0]);//할라면 하겠지만 보통 기호상수 이용 #define SIZE 10
행 rows 열 cols
#define_CRT_SECURE_NO_WARNINGS
system("cls")//출력된 화면 삭제
8진수 %o 16진수 %x
char 1바이트 
float 32비트
int 32비트
typedef enum {FALSE, TRUE } BOOL;
원주율  3.141592653589
printf 플래그(flag)  -왼쪽정렬, + 항상 부호출력, 0 출력값 앞에 공백 문자 대신 0으로 채운다., blank(' ') 출력값 앞에 양수나 0일 경우 부호 대신 0을 채운다., 8진수 출력시에는 0을 붙이고 16진수 출력시 0x를 붙인다. 
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
	printf("| 학    번 | 이  름 | 국어 | 영어 | 수학 |\n");
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
		if (p->data.studentNumber == sNo) {// 검색 성공
			return p;
		}
		else
			p = p->link;
	}

	return NULL;
}

int main() {
	//1.데이터 파일을 오픈해서 파일의 끝이 나올떄까지 반복
	FILE* fp;
	Student tmp;
	ListNode* head = NULL;

	fopen_s(&fp, "data.txt", "r");
	if (fp == NULL) {
		printf("file not found\n");
		exit(0);
	}

	while (!feof(fp)) {
		//1-1. 임시구조체 변수에 파일에서 읽은 값을 저장
		fscanf(fp, "%d %s %d %d %d", &tmp.studentNumber, tmp.name, &tmp.korean, &tmp.english, &tmp.math);

		//1-2 합계와 평균을 계산해서 임시구조체에 저장
		tmp.totalSum = tmp.korean + tmp.english + tmp.math;
		tmp.average = tmp.totalSum / 3;

		//2. 임시구조체 크기만큼 동적으로 메모리를 할당
		//3. 열결리스트 함수한테 전달해서 노드로 추가한다.
		insertNode(&head, createNode(tmp));
	}


	//4.연결리스트를 전달해서 리스트 노드를 하나씩 출력
	display(head);

	//2번 문제
	// 1. 명령어 화면 출력
	// 2. 사용자 명령 입력(추가, 출력, 종료, 검색 i, d, s,q)
	// 3. switch 분기 루틴 추가 case "i"
	// 4. 입력 i 명령인 경우, 학번, 이름, 국어, 영어, 수학 점수 입력 받아서 구조체에 저장
	// 5. 이후 루틴은 파일에서 데이터 읽어서 연결리스트에 저장하는 부분과 동일

	int command=-1;
	int sNo;

	while (command!=0) {
		printf("<<성적 관리 프로그램>>\n>> -0- 종료\n>> -1- 검색\n>> -2- 목록\n>> -3- 추가\n\n");
		scanf_s("%d", &command);

		switch (command) {
		case 3:
			printf("추가할 학생 이름: ");
			scanf_s("%s", tmp.name, 20);
			printf("학번: ");
			scanf_s("%d", &tmp.studentNumber);
			printf("국어 점수: ");
			scanf_s("%d", &tmp.korean);
			printf("영여 점수: ");
			scanf_s("%d", &tmp.english);
			printf("수학 점수: ");
			scanf_s("%d", &tmp.math);
			tmp.totalSum = tmp.korean + tmp.english + tmp.math;
			tmp.average = tmp.totalSum / 3;
			insertNode(&head, createNode(tmp));
			break;
		case 2:
			display2(head);
			break;
		case 1:
			printf("검색할 학번: ");
			scanf_s("%d", &sNo);
			ListNode* searchResult = search(head, sNo);
			printf("<이름: %s>\n<국어: %d>\n<영어: %d>\n<수학: %d>\n<총점: %d>\n", searchResult->data.name, searchResult->data.korean, searchResult->data.english, searchResult->data.math, searchResult->data.totalSum);
			break;
		case 0:
			break;
		default:
			break;
		}
	}

	//5. 열려있던 파일을 닫아준다. 메모리도 삭제해준다.
	deleteNode(&head);
	fclose(fp);

}