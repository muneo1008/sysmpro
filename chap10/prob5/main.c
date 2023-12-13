#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("메모리 할당 오류\n");
        return;
    }

    new_node->data = data;
    new_node->next = NULL;

    if (*tail == NULL) {
        *head = *tail = new_node;
    } else {
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

int delete(struct node **head, struct node **tail) {
    if (*head == NULL) {
        printf("큐가 비어있습니다.\n");
        return -1;
    }

    int deleted_data = (*head)->data;
    struct node *temp = *head;

    if (*head == *tail) {
        *head = *tail = NULL;
    } else {
        *head = (*head)->next;
    }

    free(temp);
    return deleted_data;
}

void printQueue(struct node *head) {
    printf("Print queue\n");
    while (head != NULL) {
        printf("%d\n", head->data);
        head = head->next;
    }
}

int main() {
    struct node *head = NULL;
    struct node *tail = NULL;
    int input;
    
    while (scanf("%d", &input) == 1) {
        addq(&head, &tail, input);
    }

    printQueue(head);
    
    while (head != NULL) {
        delete(&head, &tail);
    }
    return 0;
}
