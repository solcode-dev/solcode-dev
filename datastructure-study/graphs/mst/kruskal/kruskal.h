#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 간선 구조체 */
typedef struct Edge
{
  int src;    /* 시작 정점 */
  int dest;   /* 도착 정점 */
  int weight; /* 가중치 */
} Edge;

/* 그래프 구조체 (간선 리스트 기반) */
typedef struct Graph
{
  int num_vertices; /* 정점의 개수 */
  int num_edges;    /* 간선의 개수 */
  int capacity;     /* 간선 배열의 용량 */
  Edge *edges;      /* 간선 배열 */
} Graph;

/* Union-Find (Disjoint Set) 구조체 */
typedef struct UnionFind
{
  int *parent; /* 부모 노드 배열 */
  int *rank;   /* 트리의 높이 (union by rank 최적화용) */
  int size;    /* 정점의 개수 */
} UnionFind;

/* MST 결과 구조체 */
typedef struct MST
{
  Edge *edges;      /* MST를 구성하는 간선들 */
  int num_edges;    /* MST 간선의 개수 */
  int total_weight; /* MST의 총 가중치 */
} MST;

/* 그래프 관련 함수 */
Graph *create_graph(int vertices, int max_edges);
void add_edge(Graph *graph, int src, int dest, int weight);
void free_graph(Graph *graph);

/* Union-Find 관련 함수 */
UnionFind *create_union_find(int size);
int find(UnionFind *uf, int vertex);
bool union_sets(UnionFind *uf, int x, int y);
void free_union_find(UnionFind *uf);

/* Kruskal 알고리즘 */
MST *kruskal_mst(Graph *graph);
void print_mst(MST *mst);
void free_mst(MST *mst);

/* 유틸리티 함수 */
int compare_edges(const void *a, const void *b);

#endif