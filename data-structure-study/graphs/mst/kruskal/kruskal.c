#include "kruskal.h"
#include <string.h>

/* ========== 그래프 관련 함수 ========== */

/**
 * 그래프 생성
 * @param vertices: 정점의 개수
 * @param max_edges: 최대 간선 개수
 * @return: 생성된 그래프 포인터
 */
Graph *create_graph(int vertices, int max_edges)
{
  if (vertices <= 0 || max_edges <= 0)
  {
    return NULL;
  }

  Graph *graph = (Graph *)malloc(sizeof(Graph));
  if (!graph)
  {
    return NULL;
  }

  graph->edges = (Edge *)malloc(max_edges * sizeof(Edge));
  if (!graph->edges)
  {
    free(graph);
    return NULL;
  }

  graph->num_vertices = vertices;
  graph->num_edges = 0;
  graph->capacity = max_edges;

  return graph;
}

/**
 * 간선 추가 (무방향 그래프이므로 한 번만 추가)
 * @param graph: 그래프 포인터
 * @param src: 시작 정점
 * @param dest: 도착 정점
 * @param weight: 가중치
 */
void add_edge(Graph *graph, int src, int dest, int weight)
{
  if (!graph || graph->num_edges >= graph->capacity)
  {
    return;
  }

  if (src < 0 || src >= graph->num_vertices ||
      dest < 0 || dest >= graph->num_vertices)
  {
    return;
  }

  graph->edges[graph->num_edges].src = src;
  graph->edges[graph->num_edges].dest = dest;
  graph->edges[graph->num_edges].weight = weight;
  graph->num_edges++;
}

/**
 * 그래프 메모리 해제
 * @param graph: 해제할 그래프 포인터
 */
void free_graph(Graph *graph)
{
  if (!graph)
  {
    return;
  }
  free(graph->edges);
  free(graph);
}

/* ========== Union-Find 관련 함수 ========== */

/**
 * Union-Find 자료구조 생성
 * @param size: 정점의 개수
 * @return: 생성된 Union-Find 포인터
 */
UnionFind *create_union_find(int size)
{
  if (size <= 0)
  {
    return NULL;
  }

  UnionFind *uf = (UnionFind *)malloc(sizeof(UnionFind));
  if (!uf)
  {
    return NULL;
  }

  uf->parent = (int *)malloc(size * sizeof(int));
  uf->rank = (int *)malloc(size * sizeof(int));

  if (!uf->parent || !uf->rank)
  {
    free(uf->parent);
    free(uf->rank);
    free(uf);
    return NULL;
  }

  uf->size = size;

  /* 초기화: 각 정점이 자기 자신의 부모 */
  for (int i = 0; i < size; i++)
  {
    uf->parent[i] = i;
    uf->rank[i] = 0;
  }

  return uf;
}

/**
 * Find 연산 (경로 압축 최적화 적용)
 * @param uf: Union-Find 포인터
 * @param vertex: 찾을 정점
 * @return: 루트 정점
 */
int find(UnionFind *uf, int vertex)
{
  if (!uf || vertex < 0 || vertex >= uf->size)
  {
    return -1;
  }

  /* 경로 압축: 루트를 찾는 과정에서 모든 노드를 루트에 직접 연결 */
  if (uf->parent[vertex] != vertex)
  {
    uf->parent[vertex] = find(uf, uf->parent[vertex]);
  }

  return uf->parent[vertex];
}

/**
 * Union 연산 (rank 기반 최적화 적용)
 * @param uf: Union-Find 포인터
 * @param x: 첫 번째 정점
 * @param y: 두 번째 정점
 * @return: 합치기 성공 여부 (이미 같은 집합이면 false)
 */
bool union_sets(UnionFind *uf, int x, int y)
{
  if (!uf)
  {
    return false;
  }

  int root_x = find(uf, x);
  int root_y = find(uf, y);

  if (root_x == -1 || root_y == -1)
  {
    return false;
  }

  /* 이미 같은 집합에 속함 (사이클 발생) */
  if (root_x == root_y)
  {
    return false;
  }

  /* Union by rank: 작은 트리를 큰 트리 아래에 붙임 */
  if (uf->rank[root_x] < uf->rank[root_y])
  {
    uf->parent[root_x] = root_y;
  }
  else if (uf->rank[root_x] > uf->rank[root_y])
  {
    uf->parent[root_y] = root_x;
  }
  else
  {
    uf->parent[root_y] = root_x;
    uf->rank[root_x]++;
  }

  return true;
}

/**
 * Union-Find 메모리 해제
 * @param uf: 해제할 Union-Find 포인터
 */
void free_union_find(UnionFind *uf)
{
  if (!uf)
  {
    return;
  }
  free(uf->parent);
  free(uf->rank);
  free(uf);
}

/* ========== Kruskal 알고리즘 ========== */

/**
 * 간선 비교 함수 (qsort용)
 * 가중치 기준 오름차순 정렬
 */
int compare_edges(const void *a, const void *b)
{
  Edge *edge_a = (Edge *)a;
  Edge *edge_b = (Edge *)b;
  return edge_a->weight - edge_b->weight;
}

/**
 * Kruskal 알고리즘으로 최소 신장 트리 찾기
 * @param graph: 그래프 포인터
 * @return: MST 결과 (호출자가 free_mst로 해제해야 함)
 */
MST *kruskal_mst(Graph *graph)
{
  if (!graph || graph->num_vertices == 0)
  {
    return NULL;
  }

  /* MST 결과 구조체 생성 */
  MST *mst = (MST *)malloc(sizeof(MST));
  if (!mst)
  {
    return NULL;
  }

  /* MST는 최대 V-1개의 간선을 가짐 */
  mst->edges = (Edge *)malloc((graph->num_vertices - 1) * sizeof(Edge));
  if (!mst->edges)
  {
    free(mst);
    return NULL;
  }

  mst->num_edges = 0;
  mst->total_weight = 0;

  /* 1단계: 모든 간선을 가중치 기준으로 정렬 */
  qsort(graph->edges, graph->num_edges, sizeof(Edge), compare_edges);

  /* 2단계: Union-Find 자료구조 초기화 */
  UnionFind *uf = create_union_find(graph->num_vertices);
  if (!uf)
  {
    free(mst->edges);
    free(mst);
    return NULL;
  }

  /* 3단계: 가중치가 작은 간선부터 선택 */
  for (int i = 0; i < graph->num_edges && mst->num_edges < graph->num_vertices - 1; i++)
  {
    Edge current_edge = graph->edges[i];

    /* 사이클을 만들지 않는 간선만 MST에 추가 */
    if (union_sets(uf, current_edge.src, current_edge.dest))
    {
      mst->edges[mst->num_edges] = current_edge;
      mst->total_weight += current_edge.weight;
      mst->num_edges++;
    }
  }

  free_union_find(uf);

  return mst;
}

/**
 * MST 결과 출력
 * @param mst: MST 포인터
 */
void print_mst(MST *mst)
{
  if (!mst)
  {
    printf("MST가 존재하지 않습니다.\n");
    return;
  }

  printf("최소 신장 트리 (MST):\n");
  printf("간선\t\t가중치\n");

  for (int i = 0; i < mst->num_edges; i++)
  {
    printf("%d - %d\t\t%d\n",
           mst->edges[i].src,
           mst->edges[i].dest,
           mst->edges[i].weight);
  }

  printf("\n총 가중치: %d\n", mst->total_weight);
}

/**
 * MST 메모리 해제
 * @param mst: 해제할 MST 포인터
 */
void free_mst(MST *mst)
{
  if (!mst)
  {
    return;
  }
  free(mst->edges);
  free(mst);
}