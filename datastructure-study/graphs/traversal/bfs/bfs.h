#ifndef BFS_H
#define BFS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 인접 리스트의 구조체 */
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

/* 큐 구조체 (BFS를 위한 원형 큐) */
typedef struct Queue
{
  int *items;
  int front;
  int rear;
  int capacity;
} Queue;

/* 그래프 관련 함수 */
Graph *create_graph(int vertices);
void add_edge(Graph *graph, int src, int dest);
void free_graph(Graph *graph);

/* 큐 관련 함수 */
Queue *create_queue(int capacity);
bool is_empty(Queue *queue);
bool is_full(Queue *queue);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue);
void free_queue(Queue *queue);

/* BFS 알고리즘 */
void bfs(Graph *graph, int start_value);
int *bfs_traversal(Graph *graph, int start_vertex, int *result_size);

#endif