#include "improved_prim.h"

int main(void)
{
  printf("=== Prim's Algorithm 비교: Basic vs Improved ===\n\n");

  /* 예제 그래프 생성 */
  Graph *graph = create_graph(6);
  if (!graph)
  {
    fprintf(stderr, "그래프 생성 실패\n");
    return 1;
  }

  /* 간선 추가 */
  add_edge(graph, 0, 1, 4);
  add_edge(graph, 0, 2, 3);
  add_edge(graph, 1, 2, 1);
  add_edge(graph, 1, 3, 2);
  add_edge(graph, 2, 3, 4);
  add_edge(graph, 3, 4, 2);
  add_edge(graph, 3, 5, 6);
  add_edge(graph, 4, 5, 3);

  printf("입력 그래프:\n");
  printf("정점 수: %d\n", graph->num_vertices);
  printf("간선: 0-1(4), 0-2(3), 1-2(1), 1-3(2), 2-3(4), 3-4(2), 3-5(6), 4-5(3)\n\n");

  /* 성능 측정 구조체 */
  Performance basic_perf, improved_perf;

  /* 기본 Prim 실행 */
  printf(">>> 기본 Prim 알고리즘 실행 중...\n\n");
  MST *mst_basic = basic_prim_mst(graph, 0, &basic_perf);

  if (!mst_basic)
  {
    fprintf(stderr, "기본 Prim MST 계산 실패\n");
    free_graph(graph);
    return 1;
  }

  print_mst(mst_basic, "기본 Prim (배열 기반)");

  /* 개선된 Prim 실행 */
  printf(">>> 개선된 Prim 알고리즘 실행 중...\n\n");
  MST *mst_improved = improved_prim_mst(graph, 0, &improved_perf);

  if (!mst_improved)
  {
    fprintf(stderr, "개선된 Prim MST 계산 실패\n");
    free_mst(mst_basic);
    free_graph(graph);
    return 1;
  }

  print_mst(mst_improved, "개선된 Prim (Min-Heap 기반)");

  /* 성능 비교 */
  compare_performance(&basic_perf, &improved_perf);

  /* 더 큰 그래프로 성능 차이 확인 */
  printf("=== 더 큰 그래프로 성능 테스트 ===\n\n");

  Graph *large_graph = create_graph(100);
  if (!large_graph)
  {
    fprintf(stderr, "큰 그래프 생성 실패\n");
    free_mst(mst_basic);
    free_mst(mst_improved);
    free_graph(graph);
    return 1;
  }

  /* 랜덤 간선 추가 (희소 그래프) */
  for (int i = 0; i < 99; i++)
  {
    add_edge(large_graph, i, i + 1, (i * 7 + 3) % 20 + 1);
  }

  /* 추가 간선으로 연결성 증가 */
  for (int i = 0; i < 50; i++)
  {
    int src = (i * 13) % 100;
    int dest = (i * 17 + 7) % 100;
    if (src != dest)
    {
      add_edge(large_graph, src, dest, (i * 11 + 5) % 15 + 1);
    }
  }

  printf("큰 그래프: 100개 정점, 약 150개 간선\n\n");

  Performance large_basic_perf, large_improved_perf;

  printf(">>> 기본 Prim 실행 중...\n");
  MST *mst_large_basic = basic_prim_mst(large_graph, 0, &large_basic_perf);
  printf("완료!\n\n");

  printf(">>> 개선된 Prim 실행 중...\n");
  MST *mst_large_improved = improved_prim_mst(large_graph, 0, &large_improved_perf);
  printf("완료!\n\n");

  if (mst_large_basic && mst_large_improved)
  {
    printf("MST 총 가중치: %d\n\n", mst_large_basic->total_weight);
    compare_performance(&large_basic_perf, &large_improved_perf);

    printf("분석:\n");
    printf("- 희소 그래프에서 개선된 Prim이 더 효율적임.\n");
    printf("- 정점 수가 증가할수록 성능 차이가 더 명확해짐.\n");
    printf("- O(V²) vs O((V+E)logV)의 차이를 확인할 수 있음.\n\n");
  }

  /* 메모리 해제 */
  free_mst(mst_basic);
  free_mst(mst_improved);
  free_mst(mst_large_basic);
  free_mst(mst_large_improved);
  free_graph(graph);
  free_graph(large_graph);

  printf("프로그램 종료\n");
  return 0;
}