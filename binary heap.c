#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the binary heap
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert an element into the binary heap
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data <= root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }

    return root;
}

// Function to find the minimum element in the binary heap
struct Node* findMin(struct Node* root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->left == NULL) {
        return root;
    }

    return findMin(root->left);
}

// Function to remove the minimum element from the binary heap
struct Node* removeMin(struct Node* root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->left == NULL) {
        struct Node* temp = root->right;
        free(root);
        return temp;
    }

    root->left = removeMin(root->left);
    return root;
}

// Function to display the elements in the binary heap using inorder traversal
void display(struct Node* root) {
    if (root != NULL) {
        display(root->left);
        printf("%d ", root->data);
        display(root->right);
    }
}

// Function to free the memory allocated to the binary heap
void freeHeap(struct Node* root) {
    if (root != NULL) {
        freeHeap(root->left);
        freeHeap(root->right);
        free(root);
    }
}

int main() {
    struct Node* root = NULL;
    int numElements;

    printf("Enter the number of elements to insert into the binary heap: ");
    scanf("%d", &numElements);

    printf("Enter the elements:\n");
    for (int i = 0; i < numElements; i++) {
        int data;
        scanf("%d", &data);
        root = insert(root, data);
    }

    printf("Binary Heap after insertion: ");
    display(root);
    printf("\n");

    while (root != NULL) {
        struct Node* minNode = findMin(root);
        printf("Removing minimum element: %d\n", minNode->data);
        root = removeMin(root);
        printf("Binary Heap after removal: ");
        display(root);
        printf("\n");
    }

    freeHeap(root);

    return 0;
}
