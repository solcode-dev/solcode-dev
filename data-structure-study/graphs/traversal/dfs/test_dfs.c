#include "dfs.h"
#include <assert.h>
#include <string.h>

/* 테스트 헬퍼 함수: 두 배열이 같은지 비교 */
bool arrays_equal(int *arr1, int *arr2, int size)
{
  for (int i = 0; i < size; i++)
  {
    if (arr1[i] != arr2[i])
    {
      return false;
    }
  }
  return true;
}

/* 테스트 1: 그래프 생성 및 해제 */
void test_graph_creation()
{
  printf("테스트 1: 그래프 생성 및 해제...\n");

  Graph *graph = create_graph(5);
  assert(graph != NULL);
  assert(graph->num_vertices == 5);
  assert(graph->adj_lists != NULL);

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

  add_edge(graph, 0, 1);
  add_edge(graph, 1, 2);

  /* 0의 인접 리스트에 1이 있는지 확인 */
  assert(graph->adj_lists[0] != NULL);
  assert(graph->adj_lists[0]->vertex == 1);

  /* 1의 인접 리스트에 0과 2가 있는지 확인 */
  assert(graph->adj_lists[1] != NULL);

  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 3: 스택 동작 */
void test_stack_operations()
{
  printf("테스트 3: 스택 동작...\n");

  Stack *stack = create_stack(5);
  assert(stack != NULL);
  assert(is_stack_empty(stack) == true);
  assert(is_stack_full(stack) == false);

  /* push 테스트 */
  push(stack, 10);
  push(stack, 20);
  push(stack, 30);
  assert(is_stack_empty(stack) == false);

  /* pop 테스트 (LIFO 확인) */
  assert(pop(stack) == 30);
  assert(pop(stack) == 20);
  assert(pop(stack) == 10);
  assert(is_stack_empty(stack) == true);

  free_stack(stack);
  printf("  ✓ 통과\n");
}

/* 테스트 4: 단순 그래프 DFS - 재귀 버전 */
void test_simple_dfs_recursive()
{
  printf("테스트 4: 단순 그래프 DFS (재귀)...\n");

  /* 3개 정점의 선형 그래프: 0 - 1 - 2 */
  Graph *graph = create_graph(3);
  add_edge(graph, 0, 1);
  add_edge(graph, 1, 2);

  int result_size;
  int *result = dfs_recursive_traversal(graph, 0, &result_size);

  assert(result != NULL);
  assert(result_size == 3);
  assert(result[0] == 0); /* 시작 정점 */

  free(result);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 5: 단순 그래프 DFS - 스택 버전 */
void test_simple_dfs_iterative()
{
  printf("테스트 5: 단순 그래프 DFS (스택)...\n");

  /* 3개 정점의 선형 그래프: 0 - 1 - 2 */
  Graph *graph = create_graph(3);
  add_edge(graph, 0, 1);
  add_edge(graph, 1, 2);

  int result_size;
  int *result = dfs_iterative_traversal(graph, 0, &result_size);

  assert(result != NULL);
  assert(result_size == 3);
  assert(result[0] == 0); /* 시작 정점 */

  free(result);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 6: 트리 구조 DFS - 재귀 버전 */
void test_tree_dfs_recursive()
{
  printf("테스트 6: 트리 구조 DFS (재귀)...\n");

  /* 트리 구조 그래프 */
  Graph *graph = create_graph(7);
  add_edge(graph, 0, 1);
  add_edge(graph, 0, 2);
  add_edge(graph, 1, 3);
  add_edge(graph, 1, 4);
  add_edge(graph, 2, 5);
  add_edge(graph, 2, 6);

  int result_size;
  int *result = dfs_recursive_traversal(graph, 0, &result_size);

  assert(result != NULL);
  assert(result_size == 7);
  assert(result[0] == 0); /* 시작 정점 */

  /* DFS는 깊이 우선이므로 한 경로를 끝까지 탐색 */
  /* 결과는 인접 리스트의 삽입 순서에 따라 달라질 수 있음 */

  free(result);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 7: 트리 구조 DFS - 스택 버전 */
void test_tree_dfs_iterative()
{
  printf("테스트 7: 트리 구조 DFS (스택)...\n");

  /* 트리 구조 그래프 */
  Graph *graph = create_graph(7);
  add_edge(graph, 0, 1);
  add_edge(graph, 0, 2);
  add_edge(graph, 1, 3);
  add_edge(graph, 1, 4);
  add_edge(graph, 2, 5);
  add_edge(graph, 2, 6);

  int result_size;
  int *result = dfs_iterative_traversal(graph, 0, &result_size);

  assert(result != NULL);
  assert(result_size == 7);
  assert(result[0] == 0); /* 시작 정점 */

  free(result);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 8: 단일 정점 그래프 */
void test_single_vertex()
{
  printf("테스트 8: 단일 정점 그래프...\n");

  Graph *graph = create_graph(1);

  int result_size;
  int *result = dfs_recursive_traversal(graph, 0, &result_size);

  assert(result != NULL);
  assert(result_size == 1);
  assert(result[0] == 0);

  free(result);

  /* 스택 버전도 테스트 */
  result = dfs_iterative_traversal(graph, 0, &result_size);
  assert(result != NULL);
  assert(result_size == 1);
  assert(result[0] == 0);

  free(result);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 9: 연결되지 않은 그래프 */
void test_disconnected_graph()
{
  printf("테스트 9: 연결되지 않은 그래프...\n");

  /* 0-1은 연결, 2-3은 연결, 하지만 두 그룹은 분리됨 */
  Graph *graph = create_graph(4);
  add_edge(graph, 0, 1);
  add_edge(graph, 2, 3);

  int result_size;
  int *result = dfs_recursive_traversal(graph, 0, &result_size);

  assert(result != NULL);
  assert(result_size == 2); /* 0과 1만 방문 */

  free(result);

  /* 스택 버전도 테스트 */
  result = dfs_iterative_traversal(graph, 0, &result_size);
  assert(result != NULL);
  assert(result_size == 2); /* 0과 1만 방문 */

  free(result);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 10: 사이클이 있는 그래프 */
void test_cyclic_graph()
{
  printf("테스트 10: 사이클이 있는 그래프...\n");

  /* 사이클: 0 - 1 - 2 - 0 */
  Graph *graph = create_graph(3);
  add_edge(graph, 0, 1);
  add_edge(graph, 1, 2);
  add_edge(graph, 2, 0);

  int result_size;
  int *result = dfs_recursive_traversal(graph, 0, &result_size);

  assert(result != NULL);
  assert(result_size == 3); /* 모든 정점 방문 */
  assert(result[0] == 0);

  free(result);

  /* 스택 버전도 테스트 */
  result = dfs_iterative_traversal(graph, 0, &result_size);
  assert(result != NULL);
  assert(result_size == 3);
  assert(result[0] == 0);

  free(result);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

int main(void)
{
  printf("\n=== DFS 유닛 테스트 시작 ===\n\n");

  test_graph_creation();
  test_add_edge();
  test_stack_operations();
  test_simple_dfs_recursive();
  test_simple_dfs_iterative();
  test_tree_dfs_recursive();
  test_tree_dfs_iterative();
  test_single_vertex();
  test_disconnected_graph();
  test_cyclic_graph();

  printf("\n=== 모든 테스트 통과! ===\n\n");

  return 0;
}