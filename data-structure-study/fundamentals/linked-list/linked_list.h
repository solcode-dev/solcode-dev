#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef int element_type;

typedef struct TagNode
{
  element_type data;
  struct TagNode *next_node;
} Node;

// 함수 원형 선언
Node *create_node(element_type data);
void destroy_node(Node *Node);
void append_node(Node **head, Node *new_node);
void insert_new_head(Node **head, Node *new_head);
void insert_after(Node *current, Node *new_node);
void insert_before(Node **head, Node *current, Node *new_head);
void destroy_all_nodes(Node **list);
void remove_node(Node **head, Node *remove);
Node *get_node_at(Node *head, int location);
int get_node_count(Node *head);

#endif