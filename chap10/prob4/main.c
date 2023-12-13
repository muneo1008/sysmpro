#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int data;
    struct node *next;
};

void push(struct node **top, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("메모리 할당 오류\n");
        return;
    }

    new_node->data = data;
    new_node->next = *top;
    *top = new_node;
}

int pop(struct node **top) {
    if (*top == NULL) {
        printf("스택이 비어있습니다.\n");
        return -1;
    }

    int popped_data = (*top)->data;
    struct node *temp = *top;
    *top = (*top)->next;
    free(temp);

    return popped_data;
}

void printStack(struct node *top) {
    printf("Print stack\n");
    while (top != NULL) {
        printf("%d\n", top->data);
        top = top->next;
    }
}

int main() {
    struct node *top = NULL;
    int input;
    while (scanf("%d", &input) == 1) {
        push(&top, input);
    }

    printStack(top);

    while (top != NULL) {
        pop(&top);
    }
    return 0;
}
