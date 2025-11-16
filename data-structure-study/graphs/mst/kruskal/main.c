#include "kruskal.h"

int main(void)
{
  printf("=== Kruskal's Algorithm (최소 신장 트리) 데모 ===\n\n");

  /* 5개의 정점과 7개의 간선을 가진 그래프 생성
   *
   * 그래프 구조:
   *        (1)
   *     0 ---- 1
   *     |   /  |
   *  (4)|  /(2)|  (3)
   *     | /    |
   *     2 ---- 3
   *     |  (5)
   *  (6)|
   *     |
   *     4
   *
   * 간선: (0-1, 1), (0-2, 4), (1-2, 2), (1-3, 3), (2-3, 5), (2-4, 6)
   */

  Graph *graph = create_graph(5, 10);
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
  printf("정점 개수: %d\n", graph->num_vertices);
  printf("간선 개수: %d\n\n", graph->num_edges);

  printf("모든 간선:\n");
  printf("간선\t\t가중치\n");
  for (int i = 0; i < graph->num_edges; i++)
  {
    printf("%d - %d\t\t%d\n",
           graph->edges[i].src,
           graph->edges[i].dest,
           graph->edges[i].weight);
  }
  printf("\n");

  /* Kruskal 알고리즘 실행 */
  MST *mst = kruskal_mst(graph);

  if (!mst)
  {
    fprintf(stderr, "MST 계산 실패\n");
    free_graph(graph);
    return 1;
  }

  /* MST 결과 출력 */
  print_mst(mst);

  printf("\n=== 다른 예제 ===\n\n");

  /* 더 복잡한 그래프 예제 */
  Graph *graph2 = create_graph(6, 15);
  if (!graph2)
  {
    fprintf(stderr, "그래프 생성 실패\n");
    free_mst(mst);
    free_graph(graph);
    return 1;
  }

  /* 6개 정점의 완전 그래프 일부 */
  add_edge(graph2, 0, 1, 4);
  add_edge(graph2, 0, 2, 3);
  add_edge(graph2, 1, 2, 1);
  add_edge(graph2, 1, 3, 2);
  add_edge(graph2, 2, 3, 4);
  add_edge(graph2, 3, 4, 2);
  add_edge(graph2, 3, 5, 6);
  add_edge(graph2, 4, 5, 3);

  printf("두 번째 그래프 - 정점: %d, 간선: %d\n\n",
         graph2->num_vertices, graph2->num_edges);

  MST *mst2 = kruskal_mst(graph2);
  if (mst2)
  {
    print_mst(mst2);
    free_mst(mst2);
  }

  /* 메모리 해제 */
  free_mst(mst);
  free_graph(graph);
  free_graph(graph2);

  printf("\n프로그램 종료\n");
  return 0;
}