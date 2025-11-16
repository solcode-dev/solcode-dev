#include "prim.h"

int main(void)
{
  printf("=== Prim's Algorithm (최소 신장 트리) 데모 ===\n\n");

  Graph *graph = create_graph(5);
  if (!graph)
  {
    fprintf(stderr, "그래프 생성 실패\n");
    return 1;
  }

  /* 간선 추가 (정점, 정점, 가중치) */
  add_edge(graph, 0, 1, 1);
  add_edge(graph, 0, 2, 4);
  add_edge(graph, 1, 2, 2);
  add_edge(graph, 1, 3, 3);
  add_edge(graph, 2, 3, 5);
  add_edge(graph, 2, 4, 6);

  printf("입력 그래프:\n");
  printf("정점 개수: %d\n\n", graph->num_vertices);

  printf("모든 간선:\n");
  printf("0-1: 가중치 1\n");
  printf("0-2: 가중치 4\n");
  printf("1-2: 가중치 2\n");
  printf("1-3: 가중치 3\n");
  printf("2-3: 가중치 5\n");
  printf("2-4: 가중치 6\n\n");

  /* Prim 알고리즘 실행 (정점 0부터 시작) */
  printf("시작 정점: 0\n\n");
  MST *mst = prim_mst(graph, 0);

  if (!mst)
  {
    fprintf(stderr, "MST 계산 실패\n");
    free_graph(graph);
    return 1;
  }

  /* MST 결과 출력 */
  print_mst(mst);

  printf("\n=== 다른 예제 ===\n\n");

  /* 더 복잡한 그래프 */
  Graph *graph2 = create_graph(6);
  if (!graph2)
  {
    fprintf(stderr, "그래프 생성 실패\n");
    free_mst(mst);
    free_graph(graph);
    return 1;
  }

  /* 6개 정점의 그래프 */
  add_edge(graph2, 0, 1, 4);
  add_edge(graph2, 0, 2, 3);
  add_edge(graph2, 1, 2, 1);
  add_edge(graph2, 1, 3, 2);
  add_edge(graph2, 2, 3, 4);
  add_edge(graph2, 3, 4, 2);
  add_edge(graph2, 3, 5, 6);
  add_edge(graph2, 4, 5, 3);

  printf("두 번째 그래프 - 정점: %d\n\n", graph2->num_vertices);

  /* 정점 0부터 시작 */
  printf("시작 정점: 0\n\n");
  MST *mst2 = prim_mst(graph2, 0);

  if (mst2)
  {
    print_mst(mst2);
    free_mst(mst2);
  }

  printf("\n=== 다른 시작 정점 ===\n\n");

  /* 정점 2부터 시작 */
  printf("시작 정점: 2\n\n");
  MST *mst3 = prim_mst(graph2, 2);

  if (mst3)
  {
    print_mst(mst3);
    free_mst(mst3);
  }

  /* 메모리 해제 */
  free_mst(mst);
  free_graph(graph);
  free_graph(graph2);

  printf("\n프로그램 종료\n");
  return 0;
}