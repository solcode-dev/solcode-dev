#include "dijkstra.h"

/* ========== 그래프 관련 함수 ========== */

/**
 * 그래프 생성
 * @param num_vertices: 노드의 개수
 * @return: 생성된 그래프 포인터
 */
Graph *create_graph(int num_vertices)
{
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  graph->num_vertices = num_vertices;
  graph->adj_list = (Edge **)malloc(num_vertices * sizeof(Edge *));

  for (int i = 0; i < num_vertices; i++)
  {
    graph->adj_list[i] = NULL;
  }

  return graph;
}

/**
 * 그래프에 간선 추가 (유향 그래프)
 * @param graph: 그래프 포인터
 * @param src: 출발 노드
 * @param dest: 목적지 노드
 * @param weight: 가중치
 */
void add_edge(Graph *graph, int src, int dest, int weight)
{
  Edge *new_edge = (Edge *)malloc(sizeof(Edge));
  new_edge->dest = dest;
  new_edge->weight = weight;
  new_edge->next = graph->adj_list[src];
  graph->adj_list[src] = new_edge;
}

/**
 * 그래프 메모리 해제
 * @param graph: 그래프 포인터
 */
void free_graph(Graph *graph)
{
  if (graph == NULL)
    return;

  for (int i = 0; i < graph->num_vertices; i++)
  {
    Edge *current = graph->adj_list[i];
    while (current != NULL)
    {
      Edge *temp = current;
      current = current->next;
      free(temp);
    }
  }

  free(graph->adj_list);
  free(graph);
}

/* ========== 최소 힙 관련 함수 ========== */

/**
 * 최소 힙 생성
 * @param capacity: 힙의 최대 용량
 * @return: 생성된 최소 힙 포인터
 */
MinHeap *create_min_heap(int capacity)
{
  MinHeap *min_heap = (MinHeap *)malloc(sizeof(MinHeap));
  min_heap->pos = (int *)malloc(capacity * sizeof(int));
  min_heap->size = 0;
  min_heap->capacity = capacity;
  min_heap->array = (MinHeapNode **)malloc(capacity * sizeof(MinHeapNode *));
  return min_heap;
}

/**
 * 두 힙 노드 교환
 */
void swap_min_heap_node(MinHeapNode **a, MinHeapNode **b)
{
  MinHeapNode *temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * 최소 힙 속성 유지 (하향식)
 * @param min_heap: 최소 힙 포인터
 * @param idx: 힙 정리를 시작할 인덱스
 */
void min_heapify(MinHeap *min_heap, int idx)
{
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < min_heap->size &&
      min_heap->array[left]->distance < min_heap->array[smallest]->distance)
  {
    smallest = left;
  }

  if (right < min_heap->size &&
      min_heap->array[right]->distance < min_heap->array[smallest]->distance)
  {
    smallest = right;
  }

  if (smallest != idx)
  {
    MinHeapNode *smallest_node = min_heap->array[smallest];
    MinHeapNode *idx_node = min_heap->array[idx];

    // 위치 추적 배열 업데이트
    min_heap->pos[smallest_node->vertex] = idx;
    min_heap->pos[idx_node->vertex] = smallest;

    // 노드 교환
    swap_min_heap_node(&min_heap->array[smallest], &min_heap->array[idx]);

    min_heapify(min_heap, smallest);
  }
}

/**
 * 힙에서 최솟값 추출
 * @param min_heap: 최소 힙 포인터
 * @return: 최소 거리를 가진 노드
 */
MinHeapNode *extract_min(MinHeap *min_heap)
{
  if (min_heap->size == 0)
    return NULL;

  MinHeapNode *root = min_heap->array[0];
  MinHeapNode *last_node = min_heap->array[min_heap->size - 1];

  min_heap->array[0] = last_node;
  min_heap->pos[root->vertex] = min_heap->size - 1;
  min_heap->pos[last_node->vertex] = 0;

  min_heap->size--;
  min_heapify(min_heap, 0);

  return root;
}

/**
 * 노드의 거리 값 감소 (우선순위 갱신)
 * @param min_heap: 최소 힙 포인터
 * @param vertex: 노드 번호
 * @param distance: 새로운 거리 값
 */
void decrease_key(MinHeap *min_heap, int vertex, int distance)
{
  int i = min_heap->pos[vertex];
  min_heap->array[i]->distance = distance;

  // 상향식으로 힙 속성 유지
  while (i > 0 && min_heap->array[i]->distance <
                      min_heap->array[(i - 1) / 2]->distance)
  {
    min_heap->pos[min_heap->array[i]->vertex] = (i - 1) / 2;
    min_heap->pos[min_heap->array[(i - 1) / 2]->vertex] = i;

    swap_min_heap_node(&min_heap->array[i], &min_heap->array[(i - 1) / 2]);

    i = (i - 1) / 2;
  }
}

/**
 * 노드가 힙에 있는지 확인
 * @param min_heap: 최소 힙 포인터
 * @param vertex: 노드 번호
 * @return: 힙에 있으면 true, 없으면 false
 */
bool is_in_min_heap(MinHeap *min_heap, int vertex)
{
  return min_heap->pos[vertex] < min_heap->size;
}

/**
 * 최소 힙 메모리 해제
 * @param min_heap: 최소 힙 포인터
 */
void free_min_heap(MinHeap *min_heap)
{
  if (min_heap == NULL)
    return;

  for (int i = 0; i < min_heap->size; i++)
  {
    free(min_heap->array[i]);
  }

  free(min_heap->array);
  free(min_heap->pos);
  free(min_heap);
}

/* ========== 다익스트라 알고리즘 ========== */

/**
 * 다익스트라 알고리즘 구현
 * @param graph: 그래프 포인터
 * @param src: 시작 노드
 * @return: 각 노드까지의 최단 거리 배열
 *
 * 시간 복잡도: O((V + E) log V)
 * - V: 노드의 개수, E: 간선의 개수
 * - 우선순위 큐를 이용한 최적화 버전
 *
 * 공간 복잡도: O(V)
 */
int *dijkstra(Graph *graph, int src)
{
  int V = graph->num_vertices;
  int *dist = (int *)malloc(V * sizeof(int));

  MinHeap *min_heap = create_min_heap(V);

  // 모든 거리를 무한대로 초기화
  for (int v = 0; v < V; v++)
  {
    dist[v] = INF;
    min_heap->array[v] = (MinHeapNode *)malloc(sizeof(MinHeapNode));
    min_heap->array[v]->vertex = v;
    min_heap->array[v]->distance = dist[v];
    min_heap->pos[v] = v;
  }

  // 시작 노드의 거리를 0으로 설정
  min_heap->array[src]->distance = 0;
  dist[src] = 0;
  decrease_key(min_heap, src, dist[src]);

  min_heap->size = V;

  // 모든 노드를 처리할 때까지 반복
  while (min_heap->size > 0)
  {
    MinHeapNode *min_node = extract_min(min_heap);
    int u = min_node->vertex;
    free(min_node);

    // 연결된 모든 간선을 확인
    Edge *edge = graph->adj_list[u];
    while (edge != NULL)
    {
      int v = edge->dest;

      // 더 짧은 경로를 발견한 경우 업데이트
      if (is_in_min_heap(min_heap, v) &&
          dist[u] != INF &&
          edge->weight + dist[u] < dist[v])
      {
        dist[v] = dist[u] + edge->weight;
        decrease_key(min_heap, v, dist[v]);
      }

      edge = edge->next;
    }
  }

  free_min_heap(min_heap);
  return dist;
}

/**
 * 최단 거리 결과 출력
 * @param dist: 최단 거리 배열
 * @param n: 노드의 개수
 * @param src: 시작 노드
 */
void print_solution(int *dist, int n, int src)
{
  printf("\n========== 다익스트라 알고리즘 결과 ==========\n");
  printf("시작 노드: %d\n\n", src);
  printf("노드\t최단 거리\n");
  printf("----\t----------\n");

  for (int i = 0; i < n; i++)
  {
    printf("%d\t", i);
    if (dist[i] == INF)
    {
      printf("도달 불가\n");
    }
    else
    {
      printf("%d\n", dist[i]);
    }
  }
  printf("=============================================\n");
}