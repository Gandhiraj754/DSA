#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure to represent the stack
struct Stack {
    int items[MAX_SIZE];
    int top;
};

// Initialize the stack
void initialize(struct Stack* stack) {
    stack->top = -1;
}

// Check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Check if the stack is full
int isFull(struct Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

// Push an element onto the stack
void push(struct Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow, cannot push element.\n");
    } else {
        stack->items[++stack->top] = value;
    }
}

// Pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow, cannot pop element.\n");
        return -1;
    } else {
        int poppedItem = stack->items[stack->top--];
        return poppedItem;
    }
}

// Peek the top element of the stack without removing it
int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty, cannot peek.\n");
        return -1;
    } else {
        return stack->items[stack->top];
    }
}

// Stock Span Problem function
void calculateSpan(int price[], int span[], int n) {
    struct Stack stack;
    initialize(&stack);

    // The span of the first day is always 1
    span[0] = 1;

    // Push the index of the first day onto the stack
    push(&stack, 0);

    // Calculate the span for the remaining days
    for (int i = 1; i < n; i++) {
        // Pop elements from the stack while the price at the current day is greater than the price at the popped index
        while (!isEmpty(&stack) && price[i] >= price[peek(&stack)])
            pop(&stack);

        // If the stack is empty, the current day's price is the highest so far
        // Otherwise, the span is the difference between the current day's index and the index at the top of the stack
        span[i] = isEmpty(&stack) ? (i + 1) : (i - peek(&stack));

        // Push the index of the current day onto the stack
        push(&stack, i);
    }
}

int main() {
    int n;
    printf("Enter the number of days: ");
    scanf("%d", &n);

    int price[MAX_SIZE];
    printf("Enter the prices for each day:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &price[i]);
    }

    int span[MAX_SIZE];
    calculateSpan(price, span, n);

    printf("Stock Span:\n");
    for (int i = 0; i < n; i++) {
        printf("Day %d: %d\n", i + 1, span[i]);
    }

    return 0;
}
