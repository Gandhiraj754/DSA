#include <stdio.h>
#include <stdlib.h>

struct btnode {
    int value;
    struct btnode* left;
    struct btnode* right;
};
typedef struct btnode node;

/* Function declarations */
void insert(node**, int);
void bfs_traverse(node*);

int main() {
    node* root = NULL;
    int num;

    printf("Enter the elements of the tree (enter 0 to exit):\n");
    while (1) {
        scanf("%d", &num);
        if (num == 0)
            break;
        insert(&root, num);
    }

    printf("Elements in the tree using breadth-first traversal (BFS):\n");
    bfs_traverse(root);

    return 0;
}

/* Function to insert a node in the BST */
void insert(node** root, int value) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    if (*root == NULL) {
        *root = newNode;
    } else {
        node* current = *root;
        while (1) {
            if (value <= current->value) {
                if (current->left == NULL) {
                    current->left = newNode;
                    break;
                } else {
                    current = current->left;
                }
            } else {
                if (current->right == NULL) {
                    current->right = newNode;
                    break;
                } else {
                    current = current->right;
                }
            }
        }
    }
}

/* Function to perform breadth-first traversal (BFS) */
void bfs_traverse(node* root) {
    if (root == NULL)
        return;

    node* queue[100];
    int front = 0;
    int rear = 0;

    queue[rear] = root;

    while (front <= rear) {
        node* current = queue[front++];
        printf("%d -> ", current->value);

        if (current->left != NULL)
            queue[++rear] = current->left;

        if (current->right != NULL)
            queue[++rear] = current->right;
    }
}
