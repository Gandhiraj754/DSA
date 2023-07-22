#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 6

int intArray[MAX];
int front = 0;
int rear = -1;
int itemCount = 0;

int peek() {
   return intArray[front];
}

bool isEmpty() {
   return itemCount == 0;
}

bool isFull() {
   return itemCount == MAX;
}

int size() {
   return itemCount;
}

void insert(int data) {
   if (!isFull()) {
      if (rear == MAX - 1) {
         rear = -1;
      }
      intArray[++rear] = data;
      itemCount++;
   }
}

int removeData() {
   int data = intArray[front++];
   if (front == MAX) {
      front = 0;
   }
   itemCount--;
   return data;
}

int main() {
   int data;
   printf("Enter elements to enqueue (enter -1 to stop):\n");
   
   while (1) {
      scanf("%d", &data);
      
      if (data == -1) {
         break;
      }
      
      insert(data);
   }

   if (isFull()) {
      printf("Queue is full!\n");
   }

   int num = removeData();
   printf("Element removed: %d\n", num);

   printf("Enter elements to enqueue (enter -1 to stop):\n");
   
   while (1) {
      scanf("%d", &data);
      
      if (data == -1) {
         break;
      }
      
      insert(data);
   }

   printf("Element at front: %d\n", peek());

   printf("----------------------\n");
   printf("index : 5 4 3 2  1  0\n");
   printf("----------------------\n");
   printf("Queue:  ");
   
   while (!isEmpty()) {
      int n = removeData();
      printf("%d ", n);
   }
   
   return 0;
}
