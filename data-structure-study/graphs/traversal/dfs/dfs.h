#ifndef DFS_H
#define DFS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 인접 리스트의 노드 구조체 */
typedef struct Node
{
  int vertex;
  struct Node *next;
} Node;

/* 그래프 구조체 */
typedef struct Graph
{
  int num_vertices;
  Node **adj_lists; /* 인접 리스트 배열 */
} Graph;

/* 스택 구조체 (반복적 DFS를 위한) */
typedef struct Stack
{
  int *items;
  int top;
  int capacity;
} Stack;

/* 그래프 관련 함수 */
Graph *create_graph(int vertices);
void add_edge(Graph *graph, int src, int dest);
void free_graph(Graph *graph);

/* 스택 관련 함수 */
Stack *create_stack(int capacity);
bool is_stack_empty(Stack *stack);
bool is_stack_full(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
void free_stack(Stack *stack);

/* DFS 알고리즘 - 재귀 버전 */
void dfs_recursive(Graph *graph, int start_vertex);
int *dfs_recursive_traversal(Graph *graph, int start_vertex, int *result_size);

/* DFS 알고리즘 - 스택 버전 */
void dfs_iterative(Graph *graph, int start_vertex);
int *dfs_iterative_traversal(Graph *graph, int start_vertex, int *result_size);

#endif