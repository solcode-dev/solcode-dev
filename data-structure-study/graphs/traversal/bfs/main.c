#include "bfs.h"

int main(void)
{
  printf("=== BFS (Breadth-First Search) 데모 ===\n\n");

  /* 6개의 정점을 가진 그래프 생성
   * 그래프 구조:
   *       0
   *      / \
   *     1   2
   *    / \   \
   *   3   4   5
   */
  Graph *graph = create_graph(6);
  if (!graph)
  {
    fprintf(stderr, "그래프 생성 실패\n");
    return 1;
  }

  /* 간선 추가 */
  add_edge(graph, 0, 1);
  add_edge(graph, 0, 2);
  add_edge(graph, 1, 3);
  add_edge(graph, 1, 4);
  add_edge(graph, 2, 5);

  printf("그래프 구조:\n");
  printf("      0\n");
  printf("     / \\\n");
  printf("    1   2\n");
  printf("   / \\   \\\n");
  printf("  3   4   5\n\n");

  /* BFS 실행 (정점 0부터 시작) */
  printf("시작 정점: 0\n");
  bfs(graph, 0);

  printf("\n");

  /* 다른 시작 정점으로 BFS 실행 */
  printf("시작 정점: 2\n");
  bfs(graph, 2);

  /* 메모리 해제 */
  free_graph(graph);

  printf("\n프로그램 종료\n");
  return 0;
}