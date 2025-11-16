#include "kruskal.h"
#include <assert.h>

/* 테스트 1: 그래프 생성 및 해제 */
void test_graph_creation()
{
  printf("테스트 1: 그래프 생성 및 해제...\n");

  Graph *graph = create_graph(5, 10);
  assert(graph != NULL);
  assert(graph->num_vertices == 5);
  assert(graph->num_edges == 0);
  assert(graph->capacity == 10);

  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 2: 간선 추가 */
void test_add_edge()
{
  printf("테스트 2: 간선 추가...\n");

  Graph *graph = create_graph(3, 5);
  assert(graph != NULL);

  add_edge(graph, 0, 1, 5);
  assert(graph->num_edges == 1);
  assert(graph->edges[0].src == 0);
  assert(graph->edges[0].dest == 1);
  assert(graph->edges[0].weight == 5);

  add_edge(graph, 1, 2, 3);
  assert(graph->num_edges == 2);

  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 3: Union-Find 생성 */
void test_union_find_creation()
{
  printf("테스트 3: Union-Find 생성...\n");

  UnionFind *uf = create_union_find(5);
  assert(uf != NULL);
  assert(uf->size == 5);

  /* 초기 상태: 각 노드가 자기 자신의 부모 */
  for (int i = 0; i < 5; i++)
  {
    assert(uf->parent[i] == i);
    assert(uf->rank[i] == 0);
  }

  free_union_find(uf);
  printf("  ✓ 통과\n");
}

/* 테스트 4: Find 연산 */
void test_find_operation()
{
  printf("테스트 4: Find 연산...\n");

  UnionFind *uf = create_union_find(5);
  assert(uf != NULL);

  /* 초기 상태에서 각 노드의 루트는 자기 자신 */
  for (int i = 0; i < 5; i++)
  {
    assert(find(uf, i) == i);
  }

  /* 수동으로 부모 설정 */
  uf->parent[1] = 0;
  uf->parent[2] = 1;

  /* find는 루트를 반환해야 함 */
  assert(find(uf, 2) == 0);
  assert(find(uf, 1) == 0);

  /* 경로 압축 확인: 2의 부모가 이제 0이어야 함 */
  assert(uf->parent[2] == 0);

  free_union_find(uf);
  printf("  ✓ 통과\n");
}

/* 테스트 5: Union 연산 */
void test_union_operation()
{
  printf("테스트 5: Union 연산...\n");

  UnionFind *uf = create_union_find(5);
  assert(uf != NULL);

  /* 0과 1을 합침 */
  assert(union_sets(uf, 0, 1) == true);
  assert(find(uf, 0) == find(uf, 1));

  /* 2와 3을 합침 */
  assert(union_sets(uf, 2, 3) == true);
  assert(find(uf, 2) == find(uf, 3));

  /* 0과 2를 합침 (결과적으로 0, 1, 2, 3이 하나의 집합) */
  assert(union_sets(uf, 0, 2) == true);
  int root = find(uf, 0);
  assert(find(uf, 1) == root);
  assert(find(uf, 2) == root);
  assert(find(uf, 3) == root);

  /* 이미 같은 집합에 있으면 false 반환 */
  assert(union_sets(uf, 1, 3) == false);

  free_union_find(uf);
  printf("  ✓ 통과\n");
}

/* 테스트 6: 간선 정렬 */
void test_edge_sorting()
{
  printf("테스트 6: 간선 정렬...\n");

  Graph *graph = create_graph(4, 5);

  add_edge(graph, 0, 1, 5);
  add_edge(graph, 1, 2, 2);
  add_edge(graph, 2, 3, 8);
  add_edge(graph, 0, 3, 1);
  add_edge(graph, 1, 3, 4);

  /* 정렬 전 */
  assert(graph->edges[0].weight == 5);

  /* qsort로 정렬 */
  qsort(graph->edges, graph->num_edges, sizeof(Edge), compare_edges);

  /* 정렬 후: 1, 2, 4, 5, 8 순서 */
  assert(graph->edges[0].weight == 1);
  assert(graph->edges[1].weight == 2);
  assert(graph->edges[2].weight == 4);
  assert(graph->edges[3].weight == 5);
  assert(graph->edges[4].weight == 8);

  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 7: 단순 그래프 MST */
void test_simple_mst()
{
  printf("테스트 7: 단순 그래프 MST...\n");

  /* 3개 정점의 삼각형 그래프 */
  Graph *graph = create_graph(3, 3);
  add_edge(graph, 0, 1, 1);
  add_edge(graph, 1, 2, 2);
  add_edge(graph, 0, 2, 5);

  MST *mst = kruskal_mst(graph);

  assert(mst != NULL);
  assert(mst->num_edges == 2);    /* V-1 = 3-1 = 2 */
  assert(mst->total_weight == 3); /* 1 + 2 = 3 */

  free_mst(mst);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 8: 복잡한 그래프 MST */
void test_complex_mst()
{
  printf("테스트 8: 복잡한 그래프 MST...\n");

  Graph *graph = create_graph(5, 10);

  add_edge(graph, 0, 1, 1);
  add_edge(graph, 0, 2, 4);
  add_edge(graph, 1, 2, 2);
  add_edge(graph, 1, 3, 3);
  add_edge(graph, 2, 3, 5);
  add_edge(graph, 2, 4, 6);

  MST *mst = kruskal_mst(graph);

  assert(mst != NULL);
  assert(mst->num_edges == 4); /* V-1 = 5-1 = 4 */

  /* 예상 MST: (0-1,1), (1-2,2), (1-3,3), (2-4,6) = 총 12 */
  assert(mst->total_weight == 12);

  free_mst(mst);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 9: 단일 간선 그래프 */
void test_single_edge_graph()
{
  printf("테스트 9: 단일 간선 그래프...\n");

  Graph *graph = create_graph(2, 1);
  add_edge(graph, 0, 1, 10);

  MST *mst = kruskal_mst(graph);

  assert(mst != NULL);
  assert(mst->num_edges == 1);
  assert(mst->total_weight == 10);
  assert(mst->edges[0].weight == 10);

  free_mst(mst);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 10: 연결되지 않은 그래프 */
void test_disconnected_graph()
{
  printf("테스트 10: 연결되지 않은 그래프...\n");

  /* 두 개의 분리된 컴포넌트 */
  Graph *graph = create_graph(4, 2);
  add_edge(graph, 0, 1, 5);
  add_edge(graph, 2, 3, 3);

  MST *mst = kruskal_mst(graph);

  assert(mst != NULL);
  /* 연결되지 않은 그래프는 V-1개 미만의 간선을 가짐 */
  assert(mst->num_edges == 2);    /* 각 컴포넌트에서 1개씩 */
  assert(mst->total_weight == 8); /* 5 + 3 = 8 */

  free_mst(mst);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 11: 모든 간선이 같은 가중치 */
void test_equal_weights()
{
  printf("테스트 11: 모든 간선이 같은 가중치...\n");

  Graph *graph = create_graph(4, 6);

  /* 완전 그래프, 모든 간선 가중치 1 */
  add_edge(graph, 0, 1, 1);
  add_edge(graph, 0, 2, 1);
  add_edge(graph, 0, 3, 1);
  add_edge(graph, 1, 2, 1);
  add_edge(graph, 1, 3, 1);
  add_edge(graph, 2, 3, 1);

  MST *mst = kruskal_mst(graph);

  assert(mst != NULL);
  assert(mst->num_edges == 3);    /* V-1 = 4-1 = 3 */
  assert(mst->total_weight == 3); /* 1 + 1 + 1 = 3 */

  free_mst(mst);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

int main(void)
{
  printf("\n=== Kruskal 알고리즘 유닛 테스트 시작 ===\n\n");

  test_graph_creation();
  test_add_edge();
  test_union_find_creation();
  test_find_operation();
  test_union_operation();
  test_edge_sorting();
  test_simple_mst();
  test_complex_mst();
  test_single_edge_graph();
  test_disconnected_graph();
  test_equal_weights();

  printf("\n=== 모든 테스트 통과! ===\n\n");

  return 0;
}