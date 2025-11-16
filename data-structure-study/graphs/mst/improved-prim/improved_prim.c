#include "improved_prim.h"

/* ========== 그래프 관련 함수 ========== */

Graph *create_graph(int vertices)
{
  if (vertices <= 0)
  {
    return NULL;
  }

  Graph *graph = (Graph *)malloc(sizeof(Graph));
  if (!graph)
  {
    return NULL;
  }

  graph->num_vertices = vertices;
  graph->adj_lists = (AdjNode **)malloc(vertices * sizeof(AdjNode *));
  if (!graph->adj_lists)
  {
    free(graph);
    return NULL;
  }

  for (int i = 0; i < vertices; i++)
  {
    graph->adj_lists[i] = NULL;
  }

  return graph;
}

void add_edge(Graph *graph, int src, int dest, int weight)
{
  if (!graph || src < 0 || src >= graph->num_vertices ||
      dest < 0 || dest >= graph->num_vertices)
  {
    return;
  }

  AdjNode *new_node = (AdjNode *)malloc(sizeof(AdjNode));
  if (!new_node)
  {
    return;
  }
  new_node->vertex = dest;
  new_node->weight = weight;
  new_node->next = graph->adj_lists[src];
  graph->adj_lists[src] = new_node;

  new_node = (AdjNode *)malloc(sizeof(AdjNode));
  if (!new_node)
  {
    return;
  }
  new_node->vertex = src;
  new_node->weight = weight;
  new_node->next = graph->adj_lists[dest];
  graph->adj_lists[dest] = new_node;
}

void free_graph(Graph *graph)
{
  if (!graph)
  {
    return;
  }

  for (int i = 0; i < graph->num_vertices; i++)
  {
    AdjNode *current = graph->adj_lists[i];
    while (current)
    {
      AdjNode *temp = current;
      current = current->next;
      free(temp);
    }
  }

  free(graph->adj_lists);
  free(graph);
}

/* ========== 기본 Prim 알고리즘 (배열 기반) ========== */

/**
 * 배열에서 최소 key를 가진 정점 찾기
 * 시간 복잡도: O(V)
 * 개선 포인트: 이 부분이 Improved Prim에서는 O(log V)로 개선됨
 */
static int find_min_key(int *key, bool *in_mst, int V, int *comparisons)
{
  int min = INT_MAX;
  int min_index = -1;

  for (int v = 0; v < V; v++)
  {
    (*comparisons)++; /* 성능 측정을 위한 비교 횟수 카운트 */
    if (!in_mst[v] && key[v] < min)
    {
      min = key[v];
      min_index = v;
    }
  }

  return min_index;
}

/**
 * 기본 Prim 알고리즘 (배열 기반)
 * 시간 복잡도: O(V²)
 * - 외부 루프: V번
 * - find_min_key: O(V)
 * - 인접 정점 업데이트: O(E)
 * - 총: O(V²) (밀집 그래프에서는 효율적)
 */
MST *basic_prim_mst(Graph *graph, int start_vertex, Performance *perf)
{
  if (!graph || start_vertex < 0 || start_vertex >= graph->num_vertices)
  {
    return NULL;
  }

  clock_t start = clock();
  int comparisons = 0;

  int V = graph->num_vertices;
  int *parent = (int *)malloc(V * sizeof(int));
  int *key = (int *)malloc(V * sizeof(int));
  bool *in_mst = (bool *)malloc(V * sizeof(bool));

  if (!parent || !key || !in_mst)
  {
    free(parent);
    free(key);
    free(in_mst);
    return NULL;
  }

  /* 초기화 */
  for (int v = 0; v < V; v++)
  {
    parent[v] = -1;
    key[v] = INT_MAX;
    in_mst[v] = false;
  }

  key[start_vertex] = 0;

  /* V번 반복 */
  for (int count = 0; count < V; count++)
  {
    /* 배열에서 최소 key 찾기 - O(V) */
    int u = find_min_key(key, in_mst, V, &comparisons);

    if (u == -1)
    {
      break;
    }

    in_mst[u] = true;

    /* u의 인접 정점들의 key 업데이트 */
    AdjNode *adj = graph->adj_lists[u];
    while (adj)
    {
      int v = adj->vertex;
      comparisons++;

      if (!in_mst[v] && adj->weight < key[v])
      {
        parent[v] = u;
        key[v] = adj->weight;
      }

      adj = adj->next;
    }
  }

  /* MST 결과 생성 */
  MST *mst = (MST *)malloc(sizeof(MST));
  if (!mst)
  {
    free(parent);
    free(key);
    free(in_mst);
    return NULL;
  }

  mst->edges = (MSTEdge *)malloc((V - 1) * sizeof(MSTEdge));
  if (!mst->edges)
  {
    free(mst);
    free(parent);
    free(key);
    free(in_mst);
    return NULL;
  }

  mst->num_edges = 0;
  mst->total_weight = 0;

  for (int i = 0; i < V; i++)
  {
    if (parent[i] != -1)
    {
      mst->edges[mst->num_edges].src = parent[i];
      mst->edges[mst->num_edges].dest = i;
      mst->edges[mst->num_edges].weight = key[i];
      mst->total_weight += key[i];
      mst->num_edges++;
    }
  }

  clock_t end = clock();

  if (perf)
  {
    perf->execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    perf->comparisons = comparisons;
  }

  free(parent);
  free(key);
  free(in_mst);

  return mst;
}

/* ========== 개선된 Prim 알고리즘 (Min-Heap 기반) ========== */

/* Min-Heap 헬퍼 함수들 */

static HeapNode *create_heap_node(int vertex, int key)
{
  HeapNode *node = (HeapNode *)malloc(sizeof(HeapNode));
  if (!node)
  {
    return NULL;
  }
  node->vertex = vertex;
  node->key = key;
  return node;
}

static MinHeap *create_min_heap(int capacity)
{
  MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
  if (!heap)
  {
    return NULL;
  }

  heap->pos = (int *)malloc(capacity * sizeof(int));
  heap->array = (HeapNode **)malloc(capacity * sizeof(HeapNode *));

  if (!heap->pos || !heap->array)
  {
    free(heap->pos);
    free(heap->array);
    free(heap);
    return NULL;
  }

  heap->size = 0;
  heap->capacity = capacity;

  return heap;
}

static void swap_heap_node(HeapNode **a, HeapNode **b)
{
  HeapNode *temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * Min-Heapify 연산
 * 시간 복잡도: O(log V)
 * 개선 포인트: 배열 기반에서는 불가능한 효율적인 최소값 추출
 */
static void min_heapify(MinHeap *heap, int idx)
{
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < heap->size && heap->array[left]->key < heap->array[smallest]->key)
  {
    smallest = left;
  }

  if (right < heap->size && heap->array[right]->key < heap->array[smallest]->key)
  {
    smallest = right;
  }

  if (smallest != idx)
  {
    HeapNode *smallest_node = heap->array[smallest];
    HeapNode *idx_node = heap->array[idx];

    heap->pos[smallest_node->vertex] = idx;
    heap->pos[idx_node->vertex] = smallest;

    swap_heap_node(&heap->array[smallest], &heap->array[idx]);

    min_heapify(heap, smallest);
  }
}

static bool is_empty(MinHeap *heap)
{
  return heap->size == 0;
}

/**
 * 최소값 추출
 * 시간 복잡도: O(log V)
 * 개선 포인트: 기본 Prim의 O(V)보다 빠름
 */
static HeapNode *extract_min(MinHeap *heap)
{
  if (is_empty(heap))
  {
    return NULL;
  }

  HeapNode *root = heap->array[0];
  HeapNode *last_node = heap->array[heap->size - 1];
  heap->array[0] = last_node;

  heap->pos[root->vertex] = heap->size - 1;
  heap->pos[last_node->vertex] = 0;

  heap->size--;
  min_heapify(heap, 0);

  return root;
}

/**
 * Key 값 감소 연산
 * 시간 복잡도: O(log V)
 * 개선 포인트: 힙 구조를 이용한 효율적인 우선순위 업데이트
 */
static void decrease_key(MinHeap *heap, int vertex, int key)
{
  int i = heap->pos[vertex];
  heap->array[i]->key = key;

  while (i > 0 && heap->array[i]->key < heap->array[(i - 1) / 2]->key)
  {
    heap->pos[heap->array[i]->vertex] = (i - 1) / 2;
    heap->pos[heap->array[(i - 1) / 2]->vertex] = i;

    swap_heap_node(&heap->array[i], &heap->array[(i - 1) / 2]);

    i = (i - 1) / 2;
  }
}

static bool is_in_min_heap(MinHeap *heap, int vertex)
{
  return heap->pos[vertex] < heap->size;
}

static void free_min_heap(MinHeap *heap)
{
  if (!heap)
  {
    return;
  }

  for (int i = 0; i < heap->size; i++)
  {
    free(heap->array[i]);
  }

  free(heap->pos);
  free(heap->array);
  free(heap);
}

/**
 * 개선된 Prim 알고리즘 (Min-Heap 기반)
 * 시간 복잡도: O((V + E) log V)
 * - extract_min: V번 × O(log V) = O(V log V)
 * - decrease_key: 최대 E번 × O(log V) = O(E log V)
 * - 총: O((V + E) log V)
 *
 * 개선 효과:
 * - 희소 그래프(E << V²)에서 기본 Prim의 O(V²)보다 훨씬 빠름
 * - 밀집 그래프에서도 대부분 더 효율적
 */
MST *improved_prim_mst(Graph *graph, int start_vertex, Performance *perf)
{
  if (!graph || start_vertex < 0 || start_vertex >= graph->num_vertices)
  {
    return NULL;
  }

  clock_t start = clock();
  int comparisons = 0;

  int V = graph->num_vertices;
  int *parent = (int *)malloc(V * sizeof(int));
  int *key = (int *)malloc(V * sizeof(int));

  if (!parent || !key)
  {
    free(parent);
    free(key);
    return NULL;
  }

  MinHeap *heap = create_min_heap(V);
  if (!heap)
  {
    free(parent);
    free(key);
    return NULL;
  }

  /* 초기화 */
  for (int v = 0; v < V; v++)
  {
    parent[v] = -1;
    key[v] = INT_MAX;
    heap->array[v] = create_heap_node(v, key[v]);
    heap->pos[v] = v;
  }

  key[start_vertex] = 0;
  heap->array[start_vertex]->key = 0;
  decrease_key(heap, start_vertex, key[start_vertex]);

  heap->size = V;

  /* 힙이 빌 때까지 반복 */
  while (!is_empty(heap))
  {
    /* Min-Heap에서 최소 key 추출 - O(log V) */
    HeapNode *min_node = extract_min(heap);
    int u = min_node->vertex;
    free(min_node);

    /* u의 인접 정점 확인 */
    AdjNode *adj = graph->adj_lists[u];
    while (adj)
    {
      int v = adj->vertex;
      comparisons++;

      /* decrease_key 연산 - O(log V) */
      if (is_in_min_heap(heap, v) && adj->weight < key[v])
      {
        key[v] = adj->weight;
        parent[v] = u;
        decrease_key(heap, v, key[v]);
      }

      adj = adj->next;
    }
  }

  /* MST 결과 생성 */
  MST *mst = (MST *)malloc(sizeof(MST));
  if (!mst)
  {
    free(parent);
    free(key);
    free_min_heap(heap);
    return NULL;
  }

  mst->edges = (MSTEdge *)malloc((V - 1) * sizeof(MSTEdge));
  if (!mst->edges)
  {
    free(mst);
    free(parent);
    free(key);
    free_min_heap(heap);
    return NULL;
  }

  mst->num_edges = 0;
  mst->total_weight = 0;

  for (int i = 0; i < V; i++)
  {
    if (parent[i] != -1)
    {
      mst->edges[mst->num_edges].src = parent[i];
      mst->edges[mst->num_edges].dest = i;
      mst->edges[mst->num_edges].weight = key[i];
      mst->total_weight += key[i];
      mst->num_edges++;
    }
  }

  clock_t end = clock();

  if (perf)
  {
    perf->execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    perf->comparisons = comparisons;
  }

  free(parent);
  free(key);
  free_min_heap(heap);

  return mst;
}

/* ========== MST 및 성능 관련 함수 ========== */

void print_mst(MST *mst, const char *algorithm_name)
{
  if (!mst)
  {
    printf("MST가 존재하지 않습니다.\n");
    return;
  }

  printf("=== %s ===\n", algorithm_name);
  printf("간선\t\t가중치\n");

  for (int i = 0; i < mst->num_edges; i++)
  {
    printf("%d - %d\t\t%d\n",
           mst->edges[i].src,
           mst->edges[i].dest,
           mst->edges[i].weight);
  }

  printf("\n총 가중치: %d\n\n", mst->total_weight);
}

void free_mst(MST *mst)
{
  if (!mst)
  {
    return;
  }
  free(mst->edges);
  free(mst);
}

void compare_performance(Performance *basic, Performance *improved)
{
  printf("========== 성능 비교 ==========\n\n");

  printf("기본 Prim (배열 기반 - O(V²)):\n");
  printf("  실행 시간: %.6f 초\n", basic->execution_time);
  printf("  비교 연산: %d 회\n\n", basic->comparisons);

  printf("개선된 Prim (Min-Heap 기반 - O((V+E)logV)):\n");
  printf("  실행 시간: %.6f 초\n", improved->execution_time);
  printf("  비교 연산: %d 회\n\n", improved->comparisons);

  double speedup = basic->execution_time / improved->execution_time;
  int comparison_reduction = basic->comparisons - improved->comparisons;
  double comparison_percent = (double)comparison_reduction / basic->comparisons * 100;

  printf("개선 효과:\n");
  printf("  속도 향상: %.2fx\n", speedup);
  printf("  비교 연산 감소: %d 회 (%.1f%%)\n", comparison_reduction, comparison_percent);
  printf("\n================================\n\n");
}