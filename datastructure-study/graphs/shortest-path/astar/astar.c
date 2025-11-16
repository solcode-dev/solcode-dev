#include "astar.h"

/* ========== 맵 관련 함수 ========== */

/**
 * 맵 생성
 */
Map *create_map(int width, int height)
{
  Map *map = (Map *)malloc(sizeof(Map));
  map->width = width;
  map->height = height;

  // 모든 셀을 빈 공간으로 초기화
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      map->grid[i][j] = CELL_EMPTY;
    }
  }

  map->start.x = -1;
  map->start.y = -1;
  map->end.x = -1;
  map->end.y = -1;

  return map;
}

/**
 * 셀 타입 설정
 */
void set_cell(Map *map, int x, int y, CellType type)
{
  if (x >= 0 && x < map->width && y >= 0 && y < map->height)
  {
    map->grid[y][x] = type;
  }
}

/**
 * 시작점 설정
 */
void set_start(Map *map, int x, int y)
{
  map->start.x = x;
  map->start.y = y;
  set_cell(map, x, y, CELL_START);
}

/**
 * 목표점 설정
 */
void set_end(Map *map, int x, int y)
{
  map->end.x = x;
  map->end.y = y;
  set_cell(map, x, y, CELL_END);
}

/**
 * 맵 출력
 */
void print_map(Map *map)
{
  for (int i = 0; i < map->height; i++)
  {
    for (int j = 0; j < map->width; j++)
    {
      switch (map->grid[i][j])
      {
      case CELL_EMPTY:
        printf(". ");
        break;
      case CELL_WALL:
        printf("# ");
        break;
      case CELL_START:
        printf("S ");
        break;
      case CELL_END:
        printf("E ");
        break;
      case CELL_PATH:
        printf("* ");
        break;
      }
    }
    printf("\n");
  }
}

/**
 * 맵 메모리 해제
 */
void free_map(Map *map)
{
  free(map);
}

/* ========== 우선순위 큐 함수 ========== */

/**
 * 우선순위 큐 생성
 */
PriorityQueue *create_priority_queue(int capacity)
{
  PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
  pq->nodes = (Node **)malloc(sizeof(Node *) * capacity);
  pq->size = 0;
  pq->capacity = capacity;
  return pq;
}

/**
 * 두 노드 교환
 */
void swap_nodes(Node **a, Node **b)
{
  Node *temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * 힙 상향 조정
 */
void heapify_up(PriorityQueue *pq, int idx)
{
  if (idx == 0)
    return;

  int parent = (idx - 1) / 2;
  if (pq->nodes[idx]->f < pq->nodes[parent]->f)
  {
    swap_nodes(&pq->nodes[idx], &pq->nodes[parent]);
    heapify_up(pq, parent);
  }
}

/**
 * 힙 하향 조정
 */
void heapify_down(PriorityQueue *pq, int idx)
{
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < pq->size && pq->nodes[left]->f < pq->nodes[smallest]->f)
  {
    smallest = left;
  }

  if (right < pq->size && pq->nodes[right]->f < pq->nodes[smallest]->f)
  {
    smallest = right;
  }

  if (smallest != idx)
  {
    swap_nodes(&pq->nodes[idx], &pq->nodes[smallest]);
    heapify_down(pq, smallest);
  }
}

/**
 * 우선순위 큐에 노드 추가
 */
void pq_push(PriorityQueue *pq, Node *node)
{
  if (pq->size >= pq->capacity)
  {
    // 용량 확장
    pq->capacity *= 2;
    pq->nodes = (Node **)realloc(pq->nodes, sizeof(Node *) * pq->capacity);
  }

  pq->nodes[pq->size] = node;
  heapify_up(pq, pq->size);
  pq->size++;
}

/**
 * 우선순위 큐에서 최소값 추출
 */
Node *pq_pop(PriorityQueue *pq)
{
  if (pq->size == 0)
    return NULL;

  Node *min_node = pq->nodes[0];
  pq->nodes[0] = pq->nodes[pq->size - 1];
  pq->size--;

  if (pq->size > 0)
  {
    heapify_down(pq, 0);
  }

  return min_node;
}

/**
 * 우선순위 큐가 비어있는지 확인
 */
bool pq_is_empty(PriorityQueue *pq)
{
  return pq->size == 0;
}

/**
 * 우선순위 큐 메모리 해제
 */
void free_priority_queue(PriorityQueue *pq)
{
  free(pq->nodes);
  free(pq);
}

/* ========== A* 알고리즘 함수 ========== */

/**
 * 맨해튼 거리 계산 (휴리스틱 함수)
 * h(n) = |x1 - x2| + |y1 - y2|
 */
int manhattan_distance(Point a, Point b)
{
  return abs(a.x - b.x) + abs(a.y - b.y);
}

/**
 * 유효한 위치인지 확인
 */
bool is_valid_position(Map *map, int x, int y)
{
  return x >= 0 && x < map->width &&
         y >= 0 && y < map->height &&
         map->grid[y][x] != CELL_WALL;
}

/**
 * 노드 생성
 */
Node *create_node(Point pos, int g, int h, Node *parent)
{
  Node *node = (Node *)malloc(sizeof(Node));
  node->pos = pos;
  node->g = g;
  node->h = h;
  node->f = g + h;
  node->parent = parent;
  return node;
}

/**
 * A* 경로 찾기 알고리즘
 *
 * f(n) = g(n) + h(n)
 * - g(n): 시작점부터 현재 노드까지의 실제 비용
 * - h(n): 현재 노드부터 목표까지의 휴리스틱 예상 비용 (맨해튼 거리)
 * - f(n): 총 예상 비용
 *
 * 시간 복잡도: O(b^d) where b=branching factor, d=depth
 * 공간 복잡도: O(b^d)
 */
bool astar_search(Map *map)
{
  // 시작점과 끝점 유효성 검사
  if (map->start.x < 0 || map->end.x < 0)
  {
    printf("시작점 또는 목표점이 설정되지 않았습니다.\n");
    return false;
  }

  // 방문 체크 배열
  bool visited[MAX_GRID_SIZE][MAX_GRID_SIZE] = {false};

  // 우선순위 큐 (Open List)
  PriorityQueue *open_list = create_priority_queue(100);

  // 시작 노드 생성 및 추가
  int h = manhattan_distance(map->start, map->end);
  Node *start_node = create_node(map->start, 0, h, NULL);
  pq_push(open_list, start_node);

  // 4방향 이동 (상, 하, 좌, 우)
  int dx[] = {0, 0, -1, 1};
  int dy[] = {-1, 1, 0, 0};

  Node *goal_node = NULL;
  int nodes_explored = 0;

  // A* 메인 루프
  while (!pq_is_empty(open_list))
  {
    // f값이 가장 작은 노드 선택
    Node *current = pq_pop(open_list);
    nodes_explored++;

    int x = current->pos.x;
    int y = current->pos.y;

    // 이미 방문한 노드는 스킵
    if (visited[y][x])
    {
      free(current);
      continue;
    }

    visited[y][x] = true;

    // 목표 도달 확인
    if (x == map->end.x && y == map->end.y)
    {
      goal_node = current;
      printf("✓ 경로를 찾았습니다! (탐색한 노드 수: %d)\n", nodes_explored);
      break;
    }

    // 4방향 인접 노드 탐색
    for (int i = 0; i < 4; i++)
    {
      int nx = x + dx[i];
      int ny = y + dy[i];

      // 유효한 위치이고 방문하지 않은 경우
      if (is_valid_position(map, nx, ny) && !visited[ny][nx])
      {
        Point next_pos = {nx, ny};
        int g = current->g + 1; // 이동 비용 1
        int h = manhattan_distance(next_pos, map->end);

        Node *neighbor = create_node(next_pos, g, h, current);
        pq_push(open_list, neighbor);
      }
    }
  }

  // 경로 역추적 및 표시
  if (goal_node != NULL)
  {
    int path_length = 0;
    Node *node = goal_node->parent; // 목표는 제외

    while (node != NULL &&
           !(node->pos.x == map->start.x && node->pos.y == map->start.y))
    {
      map->grid[node->pos.y][node->pos.x] = CELL_PATH;
      path_length++;
      Node *temp = node;
      node = node->parent;
      free(temp);
    }

    if (node != NULL)
      free(node);
    free(goal_node);

    printf("경로 길이: %d 칸\n", path_length);
    free_priority_queue(open_list);
    return true;
  }
  else
  {
    printf("✗ 경로를 찾을 수 없습니다.\n");

    // 메모리 정리
    while (!pq_is_empty(open_list))
    {
      Node *node = pq_pop(open_list);
      free(node);
    }
    free_priority_queue(open_list);
    return false;
  }
}