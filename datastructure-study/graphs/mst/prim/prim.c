#include "prim.h"

/* ========== 그래프 관련 함수 ========== */

/**
 * 그래프 생성
 * @param vertices: 정점의 개수
 * @return: 생성된 그래프 포인터
 */
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
 * @param weight: 가중치
 */
void add_edge(Graph *graph, int src, int dest, int weight)
{
  if (!graph || src < 0 || src >= graph->num_vertices ||
      dest < 0 || dest >= graph->num_vertices)
  {
    return;
  }

  /* src -> dest 간선 추가 */
  AdjNode *new_node = (AdjNode *)malloc(sizeof(AdjNode));
  if (!new_node)
  {
    return;
  }
  new_node->vertex = dest;
  new_node->weight = weight;
  new_node->next = graph->adj_lists[src];
  graph->adj_lists[src] = new_node;

  /* dest -> src 간선 추가 (무방향 그래프) */
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

/* ========== Min-Heap 관련 함수 ========== */

/**
 * Min-Heap 노드 생성
 * @param vertex: 정점 번호
 * @param key: 우선순위 값
 * @return: 생성된 노드 포인터
 */
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

/**
 * Min-Heap 생성
 * @param capacity: 힙의 최대 용량
 * @return: 생성된 Min-Heap 포인터
 */
MinHeap *create_min_heap(int capacity)
{
  if (capacity <= 0)
  {
    return NULL;
  }

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

/**
 * 두 힙 노드 교환
 */
void swap_heap_node(HeapNode **a, HeapNode **b)
{
  HeapNode *temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * Min-Heapify 연산
 * @param heap: Min-Heap 포인터
 * @param idx: heapify를 시작할 인덱스
 */
void min_heapify(MinHeap *heap, int idx)
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
    /* 위치 업데이트 */
    HeapNode *smallest_node = heap->array[smallest];
    HeapNode *idx_node = heap->array[idx];

    heap->pos[smallest_node->vertex] = idx;
    heap->pos[idx_node->vertex] = smallest;

    /* 노드 교환 */
    swap_heap_node(&heap->array[smallest], &heap->array[idx]);

    min_heapify(heap, smallest);
  }
}

/**
 * 힙이 비어있는지 확인
 */
bool is_empty(MinHeap *heap)
{
  return heap->size == 0;
}

/**
 * 최소값 추출
 * @param heap: Min-Heap 포인터
 * @return: 최소값을 가진 노드
 */
HeapNode *extract_min(MinHeap *heap)
{
  if (is_empty(heap))
  {
    return NULL;
  }

  /* 루트 노드 저장 */
  HeapNode *root = heap->array[0];

  /* 마지막 노드를 루트로 이동 */
  HeapNode *last_node = heap->array[heap->size - 1];
  heap->array[0] = last_node;

  /* 위치 업데이트 */
  heap->pos[root->vertex] = heap->size - 1;
  heap->pos[last_node->vertex] = 0;

  /* 힙 크기 감소 및 heapify */
  heap->size--;
  min_heapify(heap, 0);

  return root;
}

/**
 * 특정 정점의 key 값 감소
 * @param heap: Min-Heap 포인터
 * @param vertex: 정점 번호
 * @param key: 새로운 key 값
 */
void decrease_key(MinHeap *heap, int vertex, int key)
{
  /* 힙에서 정점의 위치 찾기 */
  int i = heap->pos[vertex];

  /* key 값 업데이트 */
  heap->array[i]->key = key;

  /* 부모와 비교하며 위로 이동 */
  while (i > 0 && heap->array[i]->key < heap->array[(i - 1) / 2]->key)
  {
    /* 위치 정보 교환 */
    heap->pos[heap->array[i]->vertex] = (i - 1) / 2;
    heap->pos[heap->array[(i - 1) / 2]->vertex] = i;

    /* 노드 교환 */
    swap_heap_node(&heap->array[i], &heap->array[(i - 1) / 2]);

    /* 부모 위치로 이동 */
    i = (i - 1) / 2;
  }
}

/**
 * 정점이 힙에 있는지 확인
 * @param heap: Min-Heap 포인터
 * @param vertex: 확인할 정점
 * @return: 힙에 있으면 true, 아니면 false
 */
bool is_in_min_heap(MinHeap *heap, int vertex)
{
  if (heap->pos[vertex] < heap->size)
  {
    return true;
  }
  return false;
}

/**
 * Min-Heap 메모리 해제
 * @param heap: 해제할 Min-Heap 포인터
 */
void free_min_heap(MinHeap *heap)
{
  if (!heap)
  {
    return;
  }

  /* 남아있는 노드들 해제 */
  for (int i = 0; i < heap->size; i++)
  {
    free(heap->array[i]);
  }

  free(heap->pos);
  free(heap->array);
  free(heap);
}

/* ========== Prim 알고리즘 ========== */

/**
 * Prim 알고리즘으로 최소 신장 트리 찾기
 * @param graph: 그래프 포인터
 * @param start_vertex: 시작 정점
 * @return: MST 결과 (호출자가 free_mst로 해제해야 함)
 */
MST *prim_mst(Graph *graph, int start_vertex)
{
  if (!graph || start_vertex < 0 || start_vertex >= graph->num_vertices)
  {
    return NULL;
  }

  int V = graph->num_vertices;

  /* 부모 배열: parent[i]는 MST에서 i의 부모 */
  int *parent = (int *)malloc(V * sizeof(int));
  /* key 배열: MST에 포함되기 위한 최소 가중치 */
  int *key = (int *)malloc(V * sizeof(int));

  if (!parent || !key)
  {
    free(parent);
    free(key);
    return NULL;
  }

  /* Min-Heap 생성 */
  MinHeap *heap = create_min_heap(V);
  if (!heap)
  {
    free(parent);
    free(key);
    return NULL;
  }

  /* 모든 정점 초기화 */
  for (int v = 0; v < V; v++)
  {
    parent[v] = -1;
    key[v] = INT_MAX;
    heap->array[v] = create_heap_node(v, key[v]);
    heap->pos[v] = v;
  }

  /* 시작 정점의 key를 0으로 설정 */
  key[start_vertex] = 0;
  heap->array[start_vertex]->key = 0;
  decrease_key(heap, start_vertex, key[start_vertex]);

  heap->size = V;

  /* 힙이 빌 때까지 반복 */
  while (!is_empty(heap))
  {
    /* 최소 key를 가진 정점 추출 */
    HeapNode *min_node = extract_min(heap);
    int u = min_node->vertex;
    free(min_node);

    /* u의 모든 인접 정점 확인 */
    AdjNode *adj = graph->adj_lists[u];
    while (adj)
    {
      int v = adj->vertex;

      /* v가 아직 힙에 있고, u-v 간선의 가중치가 v의 현재 key보다 작으면 */
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

  /* MST는 V-1개의 간선을 가짐 */
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

  /* parent 배열을 이용해 MST 간선 생성 */
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

  free(parent);
  free(key);
  free_min_heap(heap);

  return mst;
}

/**
 * MST 결과 출력
 * @param mst: MST 포인터
 */
void print_mst(MST *mst)
{
  if (!mst)
  {
    printf("MST가 존재하지 않습니다.\n");
    return;
  }

  printf("최소 신장 트리 (MST):\n");
  printf("간선\t\t가중치\n");

  for (int i = 0; i < mst->num_edges; i++)
  {
    printf("%d - %d\t\t%d\n",
           mst->edges[i].src,
           mst->edges[i].dest,
           mst->edges[i].weight);
  }

  printf("\n총 가중치: %d\n", mst->total_weight);
}

/**
 * MST 메모리 해제
 * @param mst: 해제할 MST 포인터
 */
void free_mst(MST *mst)
{
  if (!mst)
  {
    return;
  }
  free(mst->edges);
  free(mst);
}