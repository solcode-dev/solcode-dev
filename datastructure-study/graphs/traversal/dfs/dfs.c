#include "dfs.h"

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

/* ========== 스택 관련 함수 ========== */

/**
 * 스택 생성
 * @param capacity: 스택의 최대 용량
 * @return: 생성된 스택 포인터
 */
Stack *create_stack(int capacity)
{
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  if (!stack)
  {
    return NULL;
  }

  stack->items = (int *)malloc(capacity * sizeof(int));
  if (!stack->items)
  {
    free(stack);
    return NULL;
  }

  stack->top = -1;
  stack->capacity = capacity;

  return stack;
}

/**
 * 스택이 비어있는지 확인
 */
bool is_stack_empty(Stack *stack)
{
  return stack->top == -1;
}

/**
 * 스택이 가득 찼는지 확인
 */
bool is_stack_full(Stack *stack)
{
  return stack->top == stack->capacity - 1;
}

/**
 * 스택에 원소 추가
 * @param stack: 스택 포인터
 * @param value: 추가할 값
 */
void push(Stack *stack, int value)
{
  if (!stack || is_stack_full(stack))
  {
    return;
  }
  stack->items[++(stack->top)] = value;
}

/**
 * 스택에서 원소 제거 및 반환
 * @param stack: 스택 포인터
 * @return: 제거된 값 (스택이 비어있으면 -1)
 */
int pop(Stack *stack)
{
  if (!stack || is_stack_empty(stack))
  {
    return -1;
  }
  return stack->items[(stack->top)--];
}

/**
 * 스택 메모리 해제
 * @param stack: 해제할 스택 포인터
 */
void free_stack(Stack *stack)
{
  if (!stack)
  {
    return;
  }
  free(stack->items);
  free(stack);
}

/* ========== DFS 알고리즘 - 재귀 버전 ========== */

/**
 * DFS 재귀 헬퍼 함수
 * @param graph: 그래프 포인터
 * @param vertex: 현재 정점
 * @param visited: 방문 여부 배열
 */
static void dfs_recursive_helper(Graph *graph, int vertex, bool *visited)
{
  /* 현재 정점 방문 처리 */
  visited[vertex] = true;
  printf("%d ", vertex);

  /* 인접한 모든 정점을 재귀적으로 방문 */
  Node *adj_node = graph->adj_lists[vertex];
  while (adj_node)
  {
    int adj_vertex = adj_node->vertex;
    if (!visited[adj_vertex])
    {
      dfs_recursive_helper(graph, adj_vertex, visited);
    }
    adj_node = adj_node->next;
  }
}

/**
 * DFS 알고리즘 - 재귀 버전 (출력)
 * @param graph: 그래프 포인터
 * @param start_vertex: 시작 정점
 */
void dfs_recursive(Graph *graph, int start_vertex)
{
  if (!graph || start_vertex < 0 || start_vertex >= graph->num_vertices)
  {
    return;
  }

  bool *visited = (bool *)calloc(graph->num_vertices, sizeof(bool));
  if (!visited)
  {
    return;
  }

  printf("DFS 탐색 순서 (재귀): ");
  dfs_recursive_helper(graph, start_vertex, visited);
  printf("\n");

  free(visited);
}

/**
 * DFS 재귀 헬퍼 함수 - 배열 버전
 */
static void dfs_recursive_traversal_helper(Graph *graph, int vertex, bool *visited,
                                           int *result, int *index)
{
  visited[vertex] = true;
  result[(*index)++] = vertex;

  Node *adj_node = graph->adj_lists[vertex];
  while (adj_node)
  {
    int adj_vertex = adj_node->vertex;
    if (!visited[adj_vertex])
    {
      dfs_recursive_traversal_helper(graph, adj_vertex, visited, result, index);
    }
    adj_node = adj_node->next;
  }
}

/**
 * DFS 알고리즘 - 재귀 버전 (배열 반환 - 테스트용)
 * @param graph: 그래프 포인터
 * @param start_vertex: 시작 정점
 * @param result_size: 결과 배열의 크기를 저장할 포인터
 * @return: DFS 탐색 순서를 담은 배열 (호출자가 free 해야 함)
 */
int *dfs_recursive_traversal(Graph *graph, int start_vertex, int *result_size)
{
  if (!graph || start_vertex < 0 || start_vertex >= graph->num_vertices || !result_size)
  {
    if (result_size)
      *result_size = 0;
    return NULL;
  }

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

  int index = 0;
  dfs_recursive_traversal_helper(graph, start_vertex, visited, result, &index);

  *result_size = index;
  free(visited);

  return result;
}

/* ========== DFS 알고리즘 - 스택 버전 ========== */

/**
 * DFS 알고리즘 - 반복 버전 (출력)
 * @param graph: 그래프 포인터
 * @param start_vertex: 시작 정점
 */
void dfs_iterative(Graph *graph, int start_vertex)
{
  if (!graph || start_vertex < 0 || start_vertex >= graph->num_vertices)
  {
    return;
  }

  bool *visited = (bool *)calloc(graph->num_vertices, sizeof(bool));
  if (!visited)
  {
    return;
  }

  Stack *stack = create_stack(graph->num_vertices);
  if (!stack)
  {
    free(visited);
    return;
  }

  printf("DFS 탐색 순서 (스택): ");

  /* 시작 정점을 스택에 추가 */
  push(stack, start_vertex);

  while (!is_stack_empty(stack))
  {
    int current = pop(stack);

    /* 이미 방문한 정점은 건너뜀 */
    if (visited[current])
    {
      continue;
    }

    /* 현재 정점 방문 처리 */
    visited[current] = true;
    printf("%d ", current);

    /* 인접한 모든 정점을 스택에 추가 (역순으로 추가하여 작은 번호부터 방문) */
    Node *adj_node = graph->adj_lists[current];

    /* 인접 리스트를 역순으로 스택에 넣기 위해 먼저 수집 */
    int *temp_adj = (int *)malloc(graph->num_vertices * sizeof(int));
    int temp_count = 0;

    while (adj_node)
    {
      int adj_vertex = adj_node->vertex;
      if (!visited[adj_vertex])
      {
        temp_adj[temp_count++] = adj_vertex;
      }
      adj_node = adj_node->next;
    }

    /* 역순으로 스택에 추가 */
    for (int i = 0; i < temp_count; i++)
    {
      push(stack, temp_adj[i]);
    }

    free(temp_adj);
  }

  printf("\n");

  free(visited);
  free_stack(stack);
}

/**
 * DFS 알고리즘 - 반복 버전 (배열 반환 - 테스트용)
 * @param graph: 그래프 포인터
 * @param start_vertex: 시작 정점
 * @param result_size: 결과 배열의 크기를 저장할 포인터
 * @return: DFS 탐색 순서를 담은 배열 (호출자가 free 해야 함)
 */
int *dfs_iterative_traversal(Graph *graph, int start_vertex, int *result_size)
{
  if (!graph || start_vertex < 0 || start_vertex >= graph->num_vertices || !result_size)
  {
    if (result_size)
      *result_size = 0;
    return NULL;
  }

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

  Stack *stack = create_stack(graph->num_vertices);
  if (!stack)
  {
    free(result);
    free(visited);
    *result_size = 0;
    return NULL;
  }

  int index = 0;
  push(stack, start_vertex);

  while (!is_stack_empty(stack))
  {
    int current = pop(stack);

    if (visited[current])
    {
      continue;
    }

    visited[current] = true;
    result[index++] = current;

    Node *adj_node = graph->adj_lists[current];
    int *temp_adj = (int *)malloc(graph->num_vertices * sizeof(int));
    int temp_count = 0;

    while (adj_node)
    {
      int adj_vertex = adj_node->vertex;
      if (!visited[adj_vertex])
      {
        temp_adj[temp_count++] = adj_vertex;
      }
      adj_node = adj_node->next;
    }

    for (int i = 0; i < temp_count; i++)
    {
      push(stack, temp_adj[i]);
    }

    free(temp_adj);
  }

  *result_size = index;

  free(visited);
  free_stack(stack);

  return result;
}