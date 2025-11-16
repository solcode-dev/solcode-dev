#include "bfs.h"

/* ========== 그래프 관련 함수 ========== */

/**
 * 그래프 생성
 * @param vertices: 정점의 개수
 * @return: 생성된 그래프 포인터
 */
Graph *create_graph(int vertices)
{
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  if (!graph)
  {
    return NULL;
  }

  graph->num_vertices = vertices;
  graph->adj_lists = (Node **)malloc(vertices * sizeof(Node *));
  if (!graph->adj_lists)
  {
    free(graph);
    return NULL;
  }

  /* 모든 인접 리스트를 NULL로 초기화 */
  for (int i = 0; i < vertices; i++)
  {
    graph->adj_lists[i] = NULL;
  }

  return graph;
}

/**
 * 간선 추가 (무방향 그래프)
 * @param graph: 그래프 포인터
 * @param src: 시작 정점
 * @param dest: 도착 정점
 */
void add_edge(Graph *graph, int src, int dest)
{
  if (!graph || src < 0 || src >= graph->num_vertices ||
      dest < 0 || dest >= graph->num_vertices)
  {
    return;
  }

  /* src -> dest 간선 추가 */
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (!new_node)
  {
    return;
  }
  new_node->vertex = dest;
  new_node->next = graph->adj_lists[src];
  graph->adj_lists[src] = new_node;

  /* dest -> src 간선 추가 (무방향 그래프) */
  new_node = (Node *)malloc(sizeof(Node));
  if (!new_node)
  {
    return;
  }
  new_node->vertex = src;
  new_node->next = graph->adj_lists[dest];
  graph->adj_lists[dest] = new_node;
}

/**
 * 그래프 메모리 해제
 * @param graph: 해제할 그래프 포인터
 */
void free_graph(Graph *graph)
{
  if (!graph)
  {
    return;
  }

  /* 모든 인접 리스트의 노드 해제 */
  for (int i = 0; i < graph->num_vertices; i++)
  {
    Node *current = graph->adj_lists[i];
    while (current)
    {
      Node *temp = current;
      current = current->next;
      free(temp);
    }
  }

  free(graph->adj_lists);
  free(graph);
}

/* ========== 큐 관련 함수 ========== */

/**
 * 큐 생성
 * @param capacity: 큐의 최대 용량
 * @return: 생성된 큐 포인터
 */
Queue *create_queue(int capacity)
{
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  if (!queue)
  {
    return NULL;
  }

  queue->items = (int *)malloc(capacity * sizeof(int));
  if (!queue->items)
  {
    free(queue);
    return NULL;
  }

  queue->front = 0;
  queue->rear = -1;
  queue->capacity = capacity;

  return queue;
}

/**
 * 큐가 비어있는지 확인
 */
bool is_empty(Queue *queue)
{
  return queue->rear < queue->front;
}

/**
 * 큐가 가득 찼는지 확인
 */
bool is_full(Queue *queue)
{
  return queue->rear == queue->capacity - 1;
}

/**
 * 큐에 원소 추가
 * @param queue: 큐 포인터
 * @param value: 추가할 값
 */
void enqueue(Queue *queue, int value)
{
  if (!queue || is_full(queue))
  {
    return;
  }
  queue->items[++(queue->rear)] = value;
}

/**
 * 큐에서 원소 제거 및 반환
 * @param queue: 큐 포인터
 * @return: 제거된 값 (큐가 비어있으면 -1)
 */
int dequeue(Queue *queue)
{
  if (!queue || is_empty(queue))
  {
    return -1;
  }
  return queue->items[(queue->front)++];
}

/**
 * 큐 메모리 해제
 * @param queue: 해제할 큐 포인터
 */
void free_queue(Queue *queue)
{
  if (!queue)
  {
    return;
  }
  free(queue->items);
  free(queue);
}

/* ========== BFS 알고리즘 ========== */

/**
 * BFS 알고리즘 (출력 버전)
 * @param graph: 그래프 포인터
 * @param start_vertex: 시작 정점
 */
void bfs(Graph *graph, int start_vertex)
{
  if (!graph || start_vertex < 0 || start_vertex >= graph->num_vertices)
  {
    return;
  }

  /* 방문 여부를 추적하는 배열 */
  bool *visited = (bool *)calloc(graph->num_vertices, sizeof(bool));
  if (!visited)
  {
    return;
  }

  /* BFS를 위한 큐 생성 */
  Queue *queue = create_queue(graph->num_vertices);
  if (!queue)
  {
    free(visited);
    return;
  }

  /* 시작 정점 방문 처리 */
  visited[start_vertex] = true;
  enqueue(queue, start_vertex);

  printf("BFS 탐색 순서: ");

  /* 큐가 빌 때까지 반복 */
  while (!is_empty(queue))
  {
    int current = dequeue(queue);
    printf("%d ", current);

    /* 현재 정점의 모든 인접 정점 확인 */
    Node *adj_node = graph->adj_lists[current];
    while (adj_node)
    {
      int adj_vertex = adj_node->vertex;

      /* 방문하지 않은 정점이면 큐에 추가 */
      if (!visited[adj_vertex])
      {
        visited[adj_vertex] = true;
        enqueue(queue, adj_vertex);
      }
      adj_node = adj_node->next;
    }
  }

  printf("\n");

  /* 메모리 해제 */
  free(visited);
  free_queue(queue);
}

/**
 * BFS 알고리즘 (배열 반환 버전 - 테스트용)
 * @param graph: 그래프 포인터
 * @param start_vertex: 시작 정점
 * @param result_size: 결과 배열의 크기를 저장할 포인터
 * @return: BFS 탐색 순서를 담은 배열 (호출자가 free 해야 함)
 */
int *bfs_traversal(Graph *graph, int start_vertex, int *result_size)
{
  if (!graph || start_vertex < 0 || start_vertex >= graph->num_vertices || !result_size)
  {
    if (result_size)
      *result_size = 0;
    return NULL;
  }

  /* 결과를 저장할 배열 */
  int *result = (int *)malloc(graph->num_vertices * sizeof(int));
  if (!result)
  {
    *result_size = 0;
    return NULL;
  }

  bool *visited = (bool *)calloc(graph->num_vertices, sizeof(bool));
  if (!visited)
  {
    free(result);
    *result_size = 0;
    return NULL;
  }

  Queue *queue = create_queue(graph->num_vertices);
  if (!queue)
  {
    free(result);
    free(visited);
    *result_size = 0;
    return NULL;
  }

  visited[start_vertex] = true;
  enqueue(queue, start_vertex);

  int index = 0;
  while (!is_empty(queue))
  {
    int current = dequeue(queue);
    result[index++] = current;

    Node *adj_node = graph->adj_lists[current];
    while (adj_node)
    {
      int adj_vertex = adj_node->vertex;
      if (!visited[adj_vertex])
      {
        visited[adj_vertex] = true;
        enqueue(queue, adj_vertex);
      }
      adj_node = adj_node->next;
    }
  }

  *result_size = index;

  free(visited);
  free_queue(queue);

  return result;
}