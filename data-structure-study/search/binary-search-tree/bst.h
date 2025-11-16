#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* BST 노드 구조체 */
typedef struct Node
{
  int data;
  struct Node *left;
  struct Node *right;
} Node;

/* BST 함수 선언 */
Node *create_node(int data);
Node *insert_node(Node *root, int data);
Node *search_node(Node *root, int data);
Node *delete_node(Node *root, int data);
Node *find_min(Node *root);

/* 순회 함수 */
void inorder_traversal(Node *root);
void preorder_traversal(Node *root);
void postorder_traversal(Node *root);

/* 메모리 해제 */
void free_tree(Node *root);

#endif // BST_H