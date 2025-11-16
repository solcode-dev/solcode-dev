#include "improved_prim.h"
#include <assert.h>

/* 테스트 1: 그래프 생성 및 해제 */
void test_graph_creation()
{
  printf("테스트 1: 그래프 생성 및 해제...\n");

  Graph *graph = create_graph(5);
  assert(graph != NULL);
  assert(graph->num_vertices == 5);

  for (int i = 0; i < 5; i++)
  {
    assert(graph->adj_lists[i] == NULL);
  }

  free_graph(graph);
  printf("테스트 통과\n");
}

/* 테스트 2: 간선 추가 */
void test_add_edge()
{
  printf("테스트 2: 간선 추가...\n");

  Graph *graph = create_graph(3);
  assert(graph != NULL);

  add_edge(graph, 0, 1, 5);

  assert(graph->adj_lists[0] != NULL);
  assert(graph->adj_lists[0]->vertex == 1);
  assert(graph->adj_lists[0]->weight == 5);

  assert(graph->adj_lists[1] != NULL);
  assert(graph->adj_lists[1]->vertex == 0);
  assert(graph->adj_lists[1]->weight == 5);

  free_graph(graph);
  printf("테스트 통과\n");
}

/* 테스트 3: 기본 Prim - 단순 그래프 */
void test_basic_prim_simple()
{
  printf("테스트 3: 기본 Prim - 단순 그래프...\n");

  Graph *graph = create_graph(3);
  add_edge(graph, 0, 1, 1);
  add_edge(graph, 1, 2, 2);
  add_edge(graph, 0, 2, 5);

  MST *mst = basic_prim_mst(graph, 0, NULL);

  assert(mst != NULL);
  assert(mst->num_edges == 2);
  assert(mst->total_weight == 3);

  free_mst(mst);
  free_graph(graph);
  printf("테스트 통과\n");
}

/* 테스트 4: 개선된 Prim - 단순 그래프 */
void test_improved_prim_simple()
{
  printf("테스트 4: 개선된 Prim - 단순 그래프...\n");

  Graph *graph = create_graph(3);
  add_edge(graph, 0, 1, 1);
  add_edge(graph, 1, 2, 2);
  add_edge(graph, 0, 2, 5);

  MST *mst = improved_prim_mst(graph, 0, NULL);

  assert(mst != NULL);
  assert(mst->num_edges == 2);
  assert(mst->total_weight == 3);

  free_mst(mst);
  free_graph(graph);
  printf("테스트 통과\n");
}

/* 테스트 5: 두 알고리즘 결과 비교 */
void test_algorithms_equal_result()
{
  printf("테스트 5: 기본 vs 개선 - 결과 동일성...\n");

  Graph *graph = create_graph(5);
  add_edge(graph, 0, 1, 1);
  add_edge(graph, 0, 2, 4);
  add_edge(graph, 1, 2, 2);
  add_edge(graph, 1, 3, 3);
  add_edge(graph, 2, 3, 5);
  add_edge(graph, 2, 4, 6);

  MST *mst_basic = basic_prim_mst(graph, 0, NULL);
  MST *mst_improved = improved_prim_mst(graph, 0, NULL);

  assert(mst_basic != NULL);
  assert(mst_improved != NULL);
  assert(mst_basic->num_edges == mst_improved->num_edges);
  assert(mst_basic->total_weight == mst_improved->total_weight);
  assert(mst_basic->total_weight == 12);

  free_mst(mst_basic);
  free_mst(mst_improved);
  free_graph(graph);
  printf("테스트 통과\n");
}

/* 테스트 6: 단일 간선 그래프 */
void test_single_edge()
{
  printf("테스트 6: 단일 간선 그래프...\n");

  Graph *graph = create_graph(2);
  add_edge(graph, 0, 1, 10);

  MST *mst_basic = basic_prim_mst(graph, 0, NULL);
  MST *mst_improved = improved_prim_mst(graph, 0, NULL);

  assert(mst_basic->num_edges == 1);
  assert(mst_improved->num_edges == 1);
  assert(mst_basic->total_weight == 10);
  assert(mst_improved->total_weight == 10);

  free_mst(mst_basic);
  free_mst(mst_improved);
  free_graph(graph);
  printf("테스트 통과\n");
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

  MST *mst1 = improved_prim_mst(graph, 0, NULL);
  MST *mst2 = improved_prim_mst(graph, 2, NULL);

  assert(mst1->total_weight == mst2->total_weight);
  assert(mst1->total_weight == 6);

  free_mst(mst1);
  free_mst(mst2);
  free_graph(graph);
  printf("테스트 통과\n");
}

/* 테스트 8: 정사각형 그래프 */
void test_square_graph()
{
  printf("테스트 8: 정사각형 그래프...\n");

  Graph *graph = create_graph(4);
  add_edge(graph, 0, 1, 1);
  add_edge(graph, 1, 2, 2);
  add_edge(graph, 2, 3, 3);
  add_edge(graph, 3, 0, 4);

  MST *mst_basic = basic_prim_mst(graph, 0, NULL);
  MST *mst_improved = improved_prim_mst(graph, 0, NULL);

  assert(mst_basic->num_edges == 3);
  assert(mst_improved->num_edges == 3);
  assert(mst_basic->total_weight == 6);
  assert(mst_improved->total_weight == 6);

  free_mst(mst_basic);
  free_mst(mst_improved);
  free_graph(graph);
  printf("테스트 통과\n");
}

/* 테스트 9: 모든 간선 같은 가중치 */
void test_equal_weights()
{
  printf("테스트 9: 모든 간선 같은 가중치...\n");

  Graph *graph = create_graph(4);
  add_edge(graph, 0, 1, 1);
  add_edge(graph, 0, 2, 1);
  add_edge(graph, 0, 3, 1);
  add_edge(graph, 1, 2, 1);
  add_edge(graph, 1, 3, 1);
  add_edge(graph, 2, 3, 1);

  MST *mst_basic = basic_prim_mst(graph, 0, NULL);
  MST *mst_improved = improved_prim_mst(graph, 0, NULL);

  assert(mst_basic->num_edges == 3);
  assert(mst_improved->num_edges == 3);
  assert(mst_basic->total_weight == 3);
  assert(mst_improved->total_weight == 3);

  free_mst(mst_basic);
  free_mst(mst_improved);
  free_graph(graph);
  printf("테스트 통과\n");
}

/* 테스트 10: 성능 측정 기능 */
void test_performance_measurement()
{
  printf("테스트 10: 성능 측정 기능...\n");

  Graph *graph = create_graph(10);
  for (int i = 0; i < 9; i++)
  {
    add_edge(graph, i, i + 1, i + 1);
  }

  Performance basic_perf, improved_perf;

  MST *mst_basic = basic_prim_mst(graph, 0, &basic_perf);
  MST *mst_improved = improved_prim_mst(graph, 0, &improved_perf);

  assert(mst_basic != NULL);
  assert(mst_improved != NULL);

  /* 성능 데이터가 측정되었는지 확인 */
  assert(basic_perf.execution_time >= 0);
  assert(improved_perf.execution_time >= 0);
  assert(basic_perf.comparisons > 0);
  assert(improved_perf.comparisons > 0);

  /* 이 케이스에서는 기본 Prim이 더 많은 비교를 수행해야 함 */
  assert(basic_perf.comparisons >= improved_perf.comparisons);

  free_mst(mst_basic);
  free_mst(mst_improved);
  free_graph(graph);
  printf("테스트 통과\n");
}

/* 테스트 11: 큰 그래프 */
void test_large_graph()
{
  printf("테스트 11: 큰 그래프 (성능 차이 확인)...\n");

  Graph *graph = create_graph(50);

  /* 선형 연결 */
  for (int i = 0; i < 49; i++)
  {
    add_edge(graph, i, i + 1, (i + 1) % 10 + 1);
  }

  /* 추가 연결 */
  for (int i = 0; i < 25; i++)
  {
    add_edge(graph, i, i + 2, (i * 2) % 15 + 1);
  }

  Performance basic_perf, improved_perf;

  MST *mst_basic = basic_prim_mst(graph, 0, &basic_perf);
  MST *mst_improved = improved_prim_mst(graph, 0, &improved_perf);

  assert(mst_basic != NULL);
  assert(mst_improved != NULL);
  assert(mst_basic->total_weight == mst_improved->total_weight);

  /* 개선된 버전이 더 적은 비교를 수행해야 함 */
  assert(improved_perf.comparisons < basic_perf.comparisons);

  printf("    기본 Prim 비교: %d 회\n", basic_perf.comparisons);
  printf("    개선 Prim 비교: %d 회\n", improved_perf.comparisons);
  printf("    감소율: %.1f%%\n",
         (1.0 - (double)improved_perf.comparisons / basic_perf.comparisons) * 100);

  free_mst(mst_basic);
  free_mst(mst_improved);
  free_graph(graph);
  printf("테스트 통과\n");
}

int main(void)
{
  printf("\n=== Improved Prim 알고리즘 유닛 테스트 시작 ===\n\n");

  test_graph_creation();
  test_add_edge();
  test_basic_prim_simple();
  test_improved_prim_simple();
  test_algorithms_equal_result();
  test_single_edge();
  test_different_start_vertex();
  test_square_graph();
  test_equal_weights();
  test_performance_measurement();
  test_large_graph();

  printf("\n=== 모든 테스트 통과! ===\n\n");

  return 0;
}