#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define INF INT_MAX

/* 그래프의 간선을 나타내는 구조체 */
typedef struct Edge
{
  int dest;          // 목적지 노드
  int weight;        // 가중치
  struct Edge *next; // 다음 간선 포인터
} Edge;

/* 그래프를 나타내는 구조체 (인접 리스트 방식) */
typedef struct Graph
{
  int num_vertices; // 노드의 개수
  Edge **adj_list;  // 인접 리스트 배열
} Graph;

/* 우선순위 큐의 노드 구조체 (최소 힙) */
typedef struct MinHeapNode
{
  int vertex;   // 노드 번호
  int distance; // 시작점으로부터의 거리
} MinHeapNode;

/* 최소 힙 구조체 */
typedef struct MinHeap
{
  int size;            // 현재 힙의 크기
  int capacity;        // 힙의 최대 용량
  int *pos;            // 각 노드의 힙 내 위치를 추적
  MinHeapNode **array; // 힙 노드 배열
} MinHeap;

/* 그래프 관련 함수 */
Graph *create_graph(int num_vertices);
void add_edge(Graph *graph, int src, int dest, int weight);
void free_graph(Graph *graph);

/* 최소 힙 관련 함수 */
MinHeap *create_min_heap(int capacity);
void swap_min_heap_node(MinHeapNode **a, MinHeapNode **b);
void min_heapify(MinHeap *min_heap, int idx);
MinHeapNode *extract_min(MinHeap *min_heap);
void decrease_key(MinHeap *min_heap, int vertex, int distance);
bool is_in_min_heap(MinHeap *min_heap, int vertex);
void free_min_heap(MinHeap *min_heap);

/* 다익스트라 알고리즘 */
int *dijkstra(Graph *graph, int src);
void print_solution(int *dist, int n, int src);

#endif // DIJKSTRA_H