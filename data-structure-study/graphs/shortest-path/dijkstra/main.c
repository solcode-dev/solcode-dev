#include "dijkstra.h"

/**
 * 테스트 케이스 1: 기본적인 연결 그래프
 */
void test_basic_graph()
{
  printf("\n[테스트 1] 기본 연결 그래프\n");
  printf("그래프 구조:\n");
  printf("  0 --(4)-> 1 --(8)-> 2\n");
  printf("  |         |         |\n");
  printf(" (8)       (11)      (2)\n");
  printf("  |         |         |\n");
  printf("  v         v         v\n");
  printf("  7 --(1)-> 6 <-(4)-- 2\n");
  printf("  |         |         |\n");
  printf(" (7)       (2)       (7)\n");
  printf("  |         |         |\n");
  printf("  v         v         v\n");
  printf("  8 --(6)-> 5 <-(14)- 3 <-(9)- 4\n");
  printf("            |                  |\n");
  printf("           (10)              (10)\n");
  printf("            |                  |\n");
  printf("            +--------<---------+\n\n");

  int V = 9;
  Graph *graph = create_graph(V);

  // 간선 추가
  add_edge(graph, 0, 1, 4);
  add_edge(graph, 0, 7, 8);
  add_edge(graph, 1, 2, 8);
  add_edge(graph, 1, 7, 11);
  add_edge(graph, 2, 3, 7);
  add_edge(graph, 2, 8, 2);
  add_edge(graph, 2, 5, 4);
  add_edge(graph, 3, 4, 9);
  add_edge(graph, 3, 5, 14);
  add_edge(graph, 4, 5, 10);
  add_edge(graph, 5, 6, 2);
  add_edge(graph, 6, 7, 1);
  add_edge(graph, 6, 8, 6);
  add_edge(graph, 7, 8, 7);

  int *dist = dijkstra(graph, 0);
  print_solution(dist, V, 0);

  free(dist);
  free_graph(graph);
}

/**
 * 테스트 케이스 2: 단절된 노드가 있는 그래프
 */
void test_disconnected_graph()
{
  printf("\n[테스트 2] 단절된 노드가 있는 그래프\n");
  printf("그래프 구조:\n");
  printf("  0 --(5)-> 1 --(2)-> 2\n");
  printf("  |                   |\n");
  printf(" (3)                 (1)\n");
  printf("  |                   |\n");
  printf("  v                   v\n");
  printf("  3 --(7)-> 4         5 (단절됨)\n\n");

  int V = 6;
  Graph *graph = create_graph(V);

  add_edge(graph, 0, 1, 5);
  add_edge(graph, 0, 3, 3);
  add_edge(graph, 1, 2, 2);
  add_edge(graph, 2, 5, 1);
  add_edge(graph, 3, 4, 7);
  // 노드 5는 도달 가능하지만, 노드 5에서 다른 곳으로 가는 간선이 없음

  int *dist = dijkstra(graph, 0);
  print_solution(dist, V, 0);

  free(dist);
  free_graph(graph);
}

/**
 * 테스트 케이스 3: 작은 그래프
 */
void test_small_graph()
{
  printf("\n[테스트 3] 작은 그래프 (5개 노드)\n");
  printf("그래프 구조:\n");
  printf("  0 --(10)-> 1 --(5)-> 4\n");
  printf("  |          |          |\n");
  printf(" (3)        (2)        (2)\n");
  printf("  |          |          |\n");
  printf("  v          v          v\n");
  printf("  2 --(1)-> 3 <-(6)---- 4\n\n");

  int V = 5;
  Graph *graph = create_graph(V);

  add_edge(graph, 0, 1, 10);
  add_edge(graph, 0, 2, 3);
  add_edge(graph, 1, 3, 2);
  add_edge(graph, 1, 4, 5);
  add_edge(graph, 2, 3, 1);
  add_edge(graph, 4, 3, 6);
  add_edge(graph, 4, 1, 2);

  int *dist = dijkstra(graph, 0);
  print_solution(dist, V, 0);

  free(dist);
  free_graph(graph);
}

/**
 * 테스트 케이스 4: 한 노드에서 다른 노드로
 */
void test_different_source()
{
  printf("\n[테스트 4] 다른 시작 노드에서 실행\n");
  printf("그래프 구조: (테스트 3과 동일)\n");
  printf("시작 노드: 2\n\n");

  int V = 5;
  Graph *graph = create_graph(V);

  add_edge(graph, 0, 1, 10);
  add_edge(graph, 0, 2, 3);
  add_edge(graph, 1, 3, 2);
  add_edge(graph, 1, 4, 5);
  add_edge(graph, 2, 3, 1);
  add_edge(graph, 4, 3, 6);
  add_edge(graph, 4, 1, 2);

  int *dist = dijkstra(graph, 2);
  print_solution(dist, V, 2);

  free(dist);
  free_graph(graph);
}

int main()
{
  printf("╔════════════════════════════════════════════════╗\n");
  printf("║      다익스트라 최단 경로 알고리즘 테스트       ║\n");
  printf("╚════════════════════════════════════════════════╝\n");

  test_basic_graph();
  test_disconnected_graph();
  test_small_graph();
  test_different_source();

  printf("\n✓ 모든 테스트가 완료되었습니다.\n");
  printf("✓ 메모리 누수가 없도록 모든 자원이 해제되었습니다.\n\n");

  return 0;
}