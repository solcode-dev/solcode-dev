#include "prim.h"
#include <assert.h>

/* 테스트 1: 그래프 생성 및 해제 */
void test_graph_creation()
{
  printf("테스트 1: 그래프 생성 및 해제...\n");

  Graph *graph = create_graph(5);
  assert(graph != NULL);
  assert(graph->num_vertices == 5);

  /* 모든 인접 리스트가 NULL로 초기화되었는지 확인 */
  for (int i = 0; i < 5; i++)
  {
    assert(graph->adj_lists[i] == NULL);
  }

  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 2: 간선 추가 */
void test_add_edge()
{
  printf("테스트 2: 간선 추가...\n");

  Graph *graph = create_graph(3);
  assert(graph != NULL);

  add_edge(graph, 0, 1, 5);

  /* 0의 인접 리스트에 1이 있는지 확인 */
  assert(graph->adj_lists[0] != NULL);
  assert(graph->adj_lists[0]->vertex == 1);
  assert(graph->adj_lists[0]->weight == 5);

  /* 1의 인접 리스트에 0이 있는지 확인 (무방향 그래프) */
  assert(graph->adj_lists[1] != NULL);
  assert(graph->adj_lists[1]->vertex == 0);
  assert(graph->adj_lists[1]->weight == 5);

  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 3: Min-Heap 생성 */
void test_min_heap_creation()
{
  printf("테스트 3: Min-Heap 생성...\n");

  MinHeap *heap = create_min_heap(5);
  assert(heap != NULL);
  assert(heap->capacity == 5);
  assert(heap->size == 0);
  assert(is_empty(heap) == true);

  free_min_heap(heap);
  printf("  ✓ 통과\n");
}

/* 테스트 4: 단순 그래프 MST */
void test_simple_mst()
{
  printf("테스트 4: 단순 그래프 MST...\n");

  /* 3개 정점의 삼각형 그래프 */
  Graph *graph = create_graph(3);
  add_edge(graph, 0, 1, 1);
  add_edge(graph, 1, 2, 2);
  add_edge(graph, 0, 2, 5);

  MST *mst = prim_mst(graph, 0);

  assert(mst != NULL);
  assert(mst->num_edges == 2);    /* V-1 = 3-1 = 2 */
  assert(mst->total_weight == 3); /* 1 + 2 = 3 */

  free_mst(mst);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 5: 복잡한 그래프 MST */
void test_complex_mst()
{
  printf("테스트 5: 복잡한 그래프 MST...\n");

  Graph *graph = create_graph(5);

  add_edge(graph, 0, 1, 1);
  add_edge(graph, 0, 2, 4);
  add_edge(graph, 1, 2, 2);
  add_edge(graph, 1, 3, 3);
  add_edge(graph, 2, 3, 5);
  add_edge(graph, 2, 4, 6);

  MST *mst = prim_mst(graph, 0);

  assert(mst != NULL);
  assert(mst->num_edges == 4); /* V-1 = 5-1 = 4 */

  /* 예상 MST: (0-1,1), (1-2,2), (1-3,3), (2-4,6) = 총 12 */
  assert(mst->total_weight == 12);

  free_mst(mst);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 6: 단일 간선 그래프 */
void test_single_edge_graph()
{
  printf("테스트 6: 단일 간선 그래프...\n");

  Graph *graph = create_graph(2);
  add_edge(graph, 0, 1, 10);

  MST *mst = prim_mst(graph, 0);

  assert(mst != NULL);
  assert(mst->num_edges == 1);
  assert(mst->total_weight == 10);

  free_mst(mst);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 7: 다른 시작 정점 */
void test_different_start_vertex()
{
  printf("테스트 7: 다른 시작 정점...\n");

  Graph *graph = create_graph(4);

  add_edge(graph, 0, 1, 1);
  add_edge(graph, 1, 2, 2);
  add_edge(graph, 2, 3, 3);
  add_edge(graph, 0, 3, 10);

  /* 정점 0부터 시작 */
  MST *mst1 = prim_mst(graph, 0);
  assert(mst1 != NULL);
  assert(mst1->total_weight == 6); /* 1 + 2 + 3 */

  /* 정점 2부터 시작 */
  MST *mst2 = prim_mst(graph, 2);
  assert(mst2 != NULL);
  assert(mst2->total_weight == 6); /* MST는 시작 정점과 무관하게 같음 */

  free_mst(mst1);
  free_mst(mst2);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 8: 정사각형 그래프 */
void test_square_graph()
{
  printf("테스트 8: 정사각형 그래프...\n");

  /*
   * 0 -- 1
   * |    |
   * 3 -- 2
   */
  Graph *graph = create_graph(4);

  add_edge(graph, 0, 1, 1);
  add_edge(graph, 1, 2, 2);
  add_edge(graph, 2, 3, 3);
  add_edge(graph, 3, 0, 4);

  MST *mst = prim_mst(graph, 0);

  assert(mst != NULL);
  assert(mst->num_edges == 3);
  assert(mst->total_weight == 6); /* 1 + 2 + 3 */

  free_mst(mst);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 9: 모든 간선이 같은 가중치 */
void test_equal_weights()
{
  printf("테스트 9: 모든 간선이 같은 가중치...\n");

  Graph *graph = create_graph(4);

  /* 완전 그래프, 모든 간선 가중치 1 */
  add_edge(graph, 0, 1, 1);
  add_edge(graph, 0, 2, 1);
  add_edge(graph, 0, 3, 1);
  add_edge(graph, 1, 2, 1);
  add_edge(graph, 1, 3, 1);
  add_edge(graph, 2, 3, 1);

  MST *mst = prim_mst(graph, 0);

  assert(mst != NULL);
  assert(mst->num_edges == 3);    /* V-1 = 4-1 = 3 */
  assert(mst->total_weight == 3); /* 1 + 1 + 1 = 3 */

  free_mst(mst);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 10: 큰 가중치 차이 */
void test_large_weight_difference()
{
  printf("테스트 10: 큰 가중치 차이...\n");

  Graph *graph = create_graph(3);

  add_edge(graph, 0, 1, 1);
  add_edge(graph, 1, 2, 1);
  add_edge(graph, 0, 2, 1000);

  MST *mst = prim_mst(graph, 0);

  assert(mst != NULL);
  assert(mst->num_edges == 2);
  assert(mst->total_weight == 2); /* 작은 가중치 선택 */

  free_mst(mst);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 11: 선형 그래프 */
void test_linear_graph()
{
  printf("테스트 11: 선형 그래프...\n");

  /* 0 - 1 - 2 - 3 - 4 */
  Graph *graph = create_graph(5);

  add_edge(graph, 0, 1, 2);
  add_edge(graph, 1, 2, 3);
  add_edge(graph, 2, 3, 1);
  add_edge(graph, 3, 4, 4);

  MST *mst = prim_mst(graph, 0);

  assert(mst != NULL);
  assert(mst->num_edges == 4);
  assert(mst->total_weight == 10); /* 2 + 3 + 1 + 4 */

  free_mst(mst);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

int main(void)
{
  printf("\n=== Prim 알고리즘 유닛 테스트 시작 ===\n\n");

  test_graph_creation();
  test_add_edge();
  test_min_heap_creation();
  test_simple_mst();
  test_complex_mst();
  test_single_edge_graph();
  test_different_start_vertex();
  test_square_graph();
  test_equal_weights();
  test_large_weight_difference();
  test_linear_graph();

  printf("\n=== 모든 테스트 통과!!! ===\n\n");

  return 0;
}