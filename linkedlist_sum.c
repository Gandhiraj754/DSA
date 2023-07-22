#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to insert a node at the end of the linked list
void insert(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to calculate the sum of numbers in the linked list
int calculateSum(struct Node* head) {
    int sum = 0;
    struct Node* current = head;

    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }

    return sum;
}

int main() {
    struct Node* head = NULL;
    int num;
    int inputCount = 0;

    printf("Enter numbers (enter -1 to stop):\n");

    while (1) {
        scanf("%d", &num);

        if (num == -1) {
            break;
        }

        insert(&head, num);
        inputCount++;
    }

    if (inputCount == 0) {
        printf("No numbers were entered.\n");
    } else {
        int sum = calculateSum(head);
        printf("Sum of the numbers: %d\n", sum);
    }

    // Free the memory occupied by the linked list
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
