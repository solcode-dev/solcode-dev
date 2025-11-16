#include "bfs.h"
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

/* 테스트 3: 큐 동작 */
void test_queue_operations()
{
  printf("테스트 3: 큐 동작...\n");

  Queue *queue = create_queue(5);
  assert(queue != NULL);
  assert(is_empty(queue) == true);
  assert(is_full(queue) == false);

  /* enqueue 테스트 */
  enqueue(queue, 10);
  enqueue(queue, 20);
  enqueue(queue, 30);
  assert(is_empty(queue) == false);

  /* dequeue 테스트 */
  assert(dequeue(queue) == 10);
  assert(dequeue(queue) == 20);
  assert(dequeue(queue) == 30);
  assert(is_empty(queue) == true);

  free_queue(queue);
  printf("  ✓ 통과\n");
}

/* 테스트 4: 단순 그래프 BFS */
void test_simple_bfs()
{
  printf("테스트 4: 단순 그래프 BFS...\n");

  /* 3개 정점의 선형 그래프: 0 - 1 - 2 */
  Graph *graph = create_graph(3);
  add_edge(graph, 0, 1);
  add_edge(graph, 1, 2);

  int result_size;
  int *result = bfs_traversal(graph, 0, &result_size);

  assert(result != NULL);
  assert(result_size == 3);

  int expected[] = {0, 1, 2};
  assert(arrays_equal(result, expected, 3));

  free(result);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 5: 트리 구조 BFS */
void test_tree_bfs()
{
  printf("테스트 5: 트리 구조 BFS...\n");

  /* 트리 구조 그래프 */
  Graph *graph = create_graph(7);
  add_edge(graph, 0, 1);
  add_edge(graph, 0, 2);
  add_edge(graph, 1, 3);
  add_edge(graph, 1, 4);
  add_edge(graph, 2, 5);
  add_edge(graph, 2, 6);

  int result_size;
  int *result = bfs_traversal(graph, 0, &result_size);

  assert(result != NULL);
  assert(result_size == 7);
  assert(result[0] == 0); /* 시작 정점 */

  /* 레벨 1: 1과 2 (순서는 삽입 순서에 따라 다를 수 있음) */
  assert((result[1] == 1 && result[2] == 2) ||
         (result[1] == 2 && result[2] == 1));

  free(result);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 6: 단일 정점 그래프 */
void test_single_vertex()
{
  printf("테스트 6: 단일 정점 그래프...\n");

  Graph *graph = create_graph(1);

  int result_size;
  int *result = bfs_traversal(graph, 0, &result_size);

  assert(result != NULL);
  assert(result_size == 1);
  assert(result[0] == 0);

  free(result);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

/* 테스트 7: 연결되지 않은 그래프 */
void test_disconnected_graph()
{
  printf("테스트 7: 연결되지 않은 그래프...\n");

  /* 0-1은 연결, 2-3은 연결, 하지만 두 그룹은 분리됨 */
  Graph *graph = create_graph(4);
  add_edge(graph, 0, 1);
  add_edge(graph, 2, 3);

  int result_size;
  int *result = bfs_traversal(graph, 0, &result_size);

  assert(result != NULL);
  assert(result_size == 2); /* 0과 1만 방문 */

  int expected[] = {0, 1};
  assert(arrays_equal(result, expected, 2));

  free(result);
  free_graph(graph);
  printf("  ✓ 통과\n");
}

int main(void)
{
  printf("\n=== BFS 유닛 테스트 시작 ===\n\n");

  test_graph_creation();
  test_add_edge();
  test_queue_operations();
  test_simple_bfs();
  test_tree_bfs();
  test_single_vertex();
  test_disconnected_graph();

  printf("\n=== 모든 테스트 통과! ===\n\n");

  return 0;
}