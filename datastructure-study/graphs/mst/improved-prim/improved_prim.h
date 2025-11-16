#ifndef IMPROVED_PRIM_H
#define IMPROVED_PRIM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

/* 인접 리스트의 노드 구조체 */
typedef struct AdjNode
{
  int vertex;
  int weight;
  struct AdjNode *next;
} AdjNode;

/* 그래프 구조체 */
typedef struct Graph
{
  int num_vertices;
  AdjNode **adj_lists;
} Graph;

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

/* Min-Heap 노드 (Improved Prim용) */
typedef struct HeapNode
{
  int vertex;
  int key;
} HeapNode;

/* Min-Heap 구조체 (Improved Prim용) */
typedef struct MinHeap
{
  int size;
  int capacity;
  int *pos; /* 정점이 힙에서 위치한 인덱스 */
  HeapNode **array;
} MinHeap;

/* 성능 측정 구조체 */
typedef struct Performance
{
  double execution_time; /* 실행 시간 (초) */
  int comparisons;       /* 비교 연산 횟수 */
} Performance;

/* 그래프 관련 함수 */
Graph *create_graph(int vertices);
void add_edge(Graph *graph, int src, int dest, int weight);
void free_graph(Graph *graph);

/* 기본 Prim 알고리즘 (배열 기반 - O(V²)) */
MST *basic_prim_mst(Graph *graph, int start_vertex, Performance *perf);

/* 개선된 Prim 알고리즘 (Min-Heap 기반 - O((V+E) log V)) */
MST *improved_prim_mst(Graph *graph, int start_vertex, Performance *perf);

/* MST 관련 함수 */
void print_mst(MST *mst, const char *algorithm_name);
void free_mst(MST *mst);

/* 성능 비교 함수 */
void compare_performance(Performance *basic, Performance *improved);

#endif