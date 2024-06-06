#include <stdio.h>
#include <stdlib.h>
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

void bubble_down(heap_t *node) {
    while (node) {
        heap_t *largest = node;
        if (node->left && node->left->value > largest->value) {
            largest = node->left;
        }
        if (node->right && node->right->value > largest->value) {
            largest = node->right;
        }
        if (largest != node) {
            swap_values(node, largest);
            node = largest;
        } else {
            break;
        }
    }
}

heap_t *get_last_node(heap_t *root) {
    if (!root)
        return NULL;

    heap_t *queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
    heap_t *last = root;

    while (front < rear) {
        last = queue[front++];
        if (last->left)
            queue[rear++] = last->left;
        if (last->right)
            queue[rear++] = last->right;
    }

    return last;
}

int heap_extract(heap_t **root) {
    if (!root || !*root)
        return 0;

    int extracted_value = (*root)->value;
    heap_t *last_node = get_last_node(*root);

    if (last_node == *root) {
        free(*root);
        *root = NULL;
        return extracted_value;
    }

    if (last_node->parent->left == last_node)
        last_node->parent->left = NULL;
    else
        last_node->parent->right = NULL;

    (*root)->value = last_node->value;
    free(last_node);

    bubble_down(*root);

    return extracted_value;
}

heap_t *heap_insert(heap_t **root, int value) {
    if (!root)
        return NULL;
    if (!*root) {
        *root = create_node(value, NULL);
        return *root;
    }

    heap_t *queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = *root;

    while (front < rear) {
        heap_t *current = queue[front++];
        
        if (!current->left) {
            current->left = create_node(value, current);
            bubble_down(current->left);
            return current->left;
        } else {
            queue[rear++] = current->left;
        }

        if (!current->right) {
            current->right = create_node(value, current);
            bubble_down(current->right);
            return current->right;
        } else {
            queue[rear++] = current->right;
        }
    }

    return NULL;
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
    heap_t *root = NULL;

    heap_insert(&root, 50);
    heap_insert(&root, 40);
    heap_insert(&root, 30);
    heap_insert(&root, 20);
    heap_insert(&root, 10);

    print_heap(root, 0);

    int extracted_value = heap_extract(&root);
    printf("\nExtracted value: %d\n\n", extracted_value);

    print_heap(root, 0);

    return 0;
}
