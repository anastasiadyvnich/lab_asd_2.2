#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertInEnd(Node** first, Node** last, int data) {
    Node* newNode = createNode(data);
    if (*first == NULL) {
        *first = newNode;
        *last = newNode;
    }
    else {
        newNode->prev = *last;
        (*last)->next = newNode;
        *last = newNode;
    }
}

int calcList(Node* first, Node* last) {
    int result = 0;
    Node* start = first;
    Node* end = last;

    while (start != end && start->prev != end) {
        result += (start->data * end->data);
        start = start->next;
        end = end->prev;
    }

    if (start == end)
        result += (start->data * end->data);

    return result;
}

void printSteps(Node* first, Node* last) {
    Node* start = first;
    Node* end = last;
    int isFirst = 1;

    while (start != end && start->prev != end) {
        if (!isFirst)
            printf(" + ");
        printf("%d * %d", start->data, end->data);

        start = start->next;
        end = end->prev;
        isFirst = 0;
    }

    if (start == end) {
        if (!isFirst)
            printf(" + ");
        printf("%d * %d", start->data, end->data);
    }

    printf(" = ");
}

void clearList(Node* first) {
    Node* current = first;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    int n;
    printf("Enter n: ");
    scanf_s("%d", &n);

    Node* first = NULL;
    Node* last = NULL;

    for (int i = 1; i <= 2 * n; i++) {
        insertInEnd(&first, &last, i);
    }

    int res = calcList(first, last);

    printSteps(first, last);
    printf("%d\n", res);

    clearList(first);

    return 0;
}