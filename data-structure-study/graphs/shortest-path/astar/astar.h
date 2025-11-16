#ifndef ASTAR_H
#define ASTAR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define MAX_GRID_SIZE 50

/* 그리드 셀 타입 */
typedef enum
{
  CELL_EMPTY = 0, // 빈 공간
  CELL_WALL = 1,  // 벽/장애물
  CELL_START = 2, // 시작점
  CELL_END = 3,   // 목표점
  CELL_PATH = 4   // 찾은 경로
} CellType;

/* 좌표를 나타내는 구조체 */
typedef struct
{
  int x;
  int y;
} Point;

/* A* 노드 구조체 */
typedef struct Node
{
  Point pos;           // 현재 위치
  int g;               // 시작점부터 현재까지의 실제 비용
  int h;               // 현재부터 목표까지의 휴리스틱 예상 비용
  int f;               // f = g + h (총 예상 비용)
  struct Node *parent; // 경로 역추적용 부모 노드
} Node;

/* 그리드 맵 구조체 */
typedef struct
{
  int width;
  int height;
  CellType grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
  Point start;
  Point end;
} Map;

/* 우선순위 큐 (최소 힙) */
typedef struct
{
  Node **nodes;
  int size;
  int capacity;
} PriorityQueue;

/* 맵 관련 함수 */
Map *create_map(int width, int height);
void set_cell(Map *map, int x, int y, CellType type);
void set_start(Map *map, int x, int y);
void set_end(Map *map, int x, int y);
void print_map(Map *map);
void free_map(Map *map);

/* 우선순위 큐 함수 */
PriorityQueue *create_priority_queue(int capacity);
void pq_push(PriorityQueue *pq, Node *node);
Node *pq_pop(PriorityQueue *pq);
bool pq_is_empty(PriorityQueue *pq);
void free_priority_queue(PriorityQueue *pq);

/* A* 알고리즘 함수 */
int manhattan_distance(Point a, Point b);
bool is_valid_position(Map *map, int x, int y);
Node *create_node(Point pos, int g, int h, Node *parent);
bool astar_search(Map *map);

#endif // ASTAR_H