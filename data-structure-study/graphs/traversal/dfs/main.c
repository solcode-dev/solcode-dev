#include "dfs.h"

int main(void)
{
  printf("=== DFS (Depth-First Search) 데모 ===\n\n");

  /* 7개의 정점을 가진 그래프 생성
   * 그래프 구조:
   *       0
   *      / \
   *     1   2
   *    / \   \
   *   3   4   5
   *        \
   *         6
   */
  Graph *graph = create_graph(7);
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
  add_edge(graph, 4, 6);

  printf("그래프 구조:\n");
  printf("      0\n");
  printf("     / \\\n");
  printf("    1   2\n");
  printf("   / \\   \\\n");
  printf("  3   4   5\n");
  printf("       \\\n");
  printf("        6\n\n");

  printf("=== 재귀 버전 DFS ===\n");
  printf("시작 정점: 0\n");
  dfs_recursive(graph, 0);

  printf("\n");

  printf("=== 스택 버전 DFS ===\n");
  printf("시작 정점: 0\n");
  dfs_iterative(graph, 0);

  printf("\n");

  /* 다른 시작 정점으로 DFS 실행 */
  printf("=== 다른 시작 정점으로 실행 ===\n");
  printf("시작 정점: 2 (재귀)\n");
  dfs_recursive(graph, 2);

  printf("\n시작 정점: 2 (스택)\n");
  dfs_iterative(graph, 2);

  /* 메모리 해제 */
  free_graph(graph);

  printf("\n프로그램 종료\n");
  return 0;
}