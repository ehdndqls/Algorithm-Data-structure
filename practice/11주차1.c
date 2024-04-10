#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define SIZE 64

int list[SIZE] = { 0 };
int listSize = 0;


void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void printList() {
    for (int i = 0; i < listSize; i++) {
        printf("%d > ", list[i]);
    }
    printf("\n\n");
}

void printPartOfList(int start, int end) {
    printf("[ ");
    for (int i = start; i <= end; i++) {
        printf("%d > ", list[i]);
    }
    printf("]\n\n");
}

/*
int partition(int left, int right) {

    int pivot = list[left];
    printf("\n-Pivot : %d-\n", pivot);
    int i = (left + 1);


    for (int j = left + 1; j <= right; j++) {
        if (list[j] < pivot) {
            if(i==j){
                i++;
                continue;
            }
            printf("swap %d - %d\n", list[i], list[j]);
            swap(&list[i], &list[j]);
            i++;
        }
    }

    swap(&list[i - 1], &list[left]);
    return i - 1;
}
*/

int partition(int left, int right) {
    int pivot = list[left];
    int low = left, high = right + 1;

    printf("\n- Pivot: %d-\n", pivot);

    do {
        do {
            low++;
        } while (low <= right && list[low] < pivot);
        do {
            high--;
        } while (high >= left && list[high] > pivot);
        printf("Low: %d, High: %d   ", list[low], list[high]);
        printPartOfList(left, right);

        if (low < high) {
            printf("Swap: %d - %d\n", list[low], list[high]);
            swap(&list[low], &list[high]);
        }
    } while (low < high);

    printf("Swap: %d - %d   (Pivot Swap)\n", list[left], list[high]);
    printPartOfList(left, right);
    swap(&list[left], &list[high]);
    return high;
}

void quickSort(int left, int right) {
    if (left < right) {	// range >= 1
        int p = partition(left, right);
        quickSort(left, p);
        quickSort(p + 1, right);
    }
}

int main() {
    FILE* fp = fopen("data10.txt", "r");
    if (!fp) {
        printf("file load error\n");
        return -1;
    }
    int tmp;
    for (int i = 0; fscanf(fp, "%d", &tmp) != EOF; i++) {
        list[i] = tmp;
        listSize++;
    }
    printf("< 정렬 전 데이터 >\n");
    printList();

    quickSort(0, listSize - 1);
    printf("\n\n");

    printf("< 정렬 후 데이터 >\n");
    printList();

    return 0;
}

