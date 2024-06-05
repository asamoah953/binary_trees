#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_trees.h"

typedef struct heap_s {
    int value;
    struct heap_s *left;
    struct heap_s *right;
    struct heap_s *parent;
} heap_t;

heap_t *create_node(int value, heap_t *parent) {
    heap_t *node = malloc(sizeof(heap_t));
    if (!node)
        return NULL;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    return node;
}

void swap_values(heap_t *a, heap_t *b) {
    int temp = a->value;
    a->value = b->value;
    b->value = temp;
}

void bubble_up(heap_t *node) {
    while (node->parent && node->value > node->parent->value) {
        swap_values(node, node->parent);
        node = node->parent;
    }
}

heap_t *heap_insert(heap_t **root, int value) {
    if (!root)
        return NULL;
    if (!*root) {
        *root = create_node(value, NULL);
        return *root;
    }

    // Perform level-order traversal to find the correct insertion point
    heap_t *queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = *root;

    while (front < rear) {
        heap_t *current = queue[front++];
        
        if (!current->left) {
            current->left = create_node(value, current);
            bubble_up(current->left);
            return current->left;
        } else {
            queue[rear++] = current->left;
        }

        if (!current->right) {
            current->right = create_node(value, current);
            bubble_up(current->right);
            return current->right;
        } else {
            queue[rear++] = current->right;
        }
    }

    return NULL;
}

heap_t *array_to_heap(int *array, size_t size) {
    if (!array || size == 0)
        return NULL;

    heap_t *root = NULL;

    for (size_t i = 0; i < size; i++) {
        if (!heap_insert(&root, array[i])) {
            // Free all previously allocated nodes in case of failure
            // This part is skipped for simplicity, but in a complete implementation,
            // you should handle freeing allocated memory to prevent memory leaks.
            return NULL;
        }
    }

    return root;
}

void print_heap(heap_t *root, int level) {
    if (root == NULL)
        return;
    print_heap(root->right, level + 1);
    for (int i = 0; i < level; i++)
        printf("   ");
    printf("%d\n", root->value);
    print_heap(root->left, level + 1);
}

int main() {
    int array[] = {10, 20, 15, 30, 40, 50, 5};
    size_t size = sizeof(array) / sizeof(array[0]);

    heap_t *root = array_to_heap(array, size);
    if (root)
        print_heap(root, 0);

    return 0;
}
