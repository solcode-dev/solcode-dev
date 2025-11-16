#ifndef PRIM_H
#define PRIM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/* 인접 리스트의 노드 구조체 */
typedef struct AdjNode
{
  int vertex; /* 인접한 정점 */
  int weight; /* 간선의 가중치 */
  struct AdjNode *next;
} AdjNode;

/* 그래프 구조체 */
typedef struct Graph
{
  int num_vertices;
  AdjNode **adj_lists; /* 인접 리스트 배열 */
} Graph;

/* Min-Heap의 노드 구조체 */
typedef struct HeapNode
{
  int vertex; /* 정점 번호 */
  int key;    /* 우선순위 (가중치) */
} HeapNode;

/* Min-Heap 구조체 */
typedef struct MinHeap
{
  int size;         /* 현재 힙의 크기 */
  int capacity;     /* 힙의 최대 용량 */
  int *pos;         /* pos[v] = 정점 v가 힙에서 위치한 인덱스 */
  HeapNode **array; /* 힙 배열 */
} MinHeap;

/* MST 간선 구조체 */
typedef struct MSTEdge
{
  int src;
  int dest;
  int weight;
} MSTEdge;

/* MST 결과 구조체 */
typedef struct MST
{
  MSTEdge *edges;
  int num_edges;
  int total_weight;
} MST;

/* 그래프 관련 함수 */
Graph *create_graph(int vertices);
void add_edge(Graph *graph, int src, int dest, int weight);
void free_graph(Graph *graph);

/* Min-Heap 관련 함수 */
MinHeap *create_min_heap(int capacity);
void swap_heap_node(HeapNode **a, HeapNode **b);
void min_heapify(MinHeap *heap, int idx);
bool is_empty(MinHeap *heap);
HeapNode *extract_min(MinHeap *heap);
void decrease_key(MinHeap *heap, int vertex, int key);
bool is_in_min_heap(MinHeap *heap, int vertex);
void free_min_heap(MinHeap *heap);

/* Prim 알고리즘 */
MST *prim_mst(Graph *graph, int start_vertex);
void print_mst(MST *mst);
void free_mst(MST *mst);

#endif