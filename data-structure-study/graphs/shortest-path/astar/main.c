#include "astar.h"

/**
 * 테스트 케이스 1: 기본 맵 (장애물 포함)
 */
void test_basic_map()
{
  printf("\n╔════════════════════════════════════════╗\n");
  printf("║  [테스트 1] 기본 맵 (10x10)            ║\n");
  printf("╚════════════════════════════════════════╝\n\n");

  Map *map = create_map(10, 10);

  // 시작점과 목표점 설정
  set_start(map, 0, 0);
  set_end(map, 9, 9);

  // 장애물 배치
  set_cell(map, 3, 0, CELL_WALL);
  set_cell(map, 3, 1, CELL_WALL);
  set_cell(map, 3, 2, CELL_WALL);
  set_cell(map, 3, 3, CELL_WALL);
  set_cell(map, 3, 4, CELL_WALL);

  set_cell(map, 6, 5, CELL_WALL);
  set_cell(map, 6, 6, CELL_WALL);
  set_cell(map, 6, 7, CELL_WALL);
  set_cell(map, 6, 8, CELL_WALL);
  set_cell(map, 6, 9, CELL_WALL);

  set_cell(map, 1, 6, CELL_WALL);
  set_cell(map, 2, 6, CELL_WALL);
  set_cell(map, 3, 6, CELL_WALL);

  printf("원본 맵:\n");
  print_map(map);

  printf("\nA* 알고리즘 실행 중...\n");
  bool found = astar_search(map);

  if (found)
  {
    printf("\n찾은 경로 (S=시작, E=끝, *=경로, #=벽):\n");
    print_map(map);
  }

  free_map(map);
}

/**
 * 테스트 케이스 2: 도달 불가능한 맵
 */
void test_unreachable_map()
{
  printf("\n╔════════════════════════════════════════╗\n");
  printf("║  [테스트 2] 도달 불가능한 맵          ║\n");
  printf("╚════════════════════════════════════════╝\n\n");

  Map *map = create_map(10, 10);

  // 시작점과 목표점 설정
  set_start(map, 0, 0);
  set_end(map, 9, 9);

  // 목표를 완전히 둘러싸는 벽 생성
  for (int i = 7; i <= 9; i++)
  {
    set_cell(map, i, 7, CELL_WALL);
    set_cell(map, i, 9, CELL_WALL);
  }
  for (int i = 7; i <= 9; i++)
  {
    set_cell(map, 7, i, CELL_WALL);
    set_cell(map, 9, i, CELL_WALL);
  }

  printf("원본 맵 (목표가 벽으로 둘러싸여 있음):\n");
  print_map(map);

  printf("\nA* 알고리즘 실행 중...\n");
  bool found = astar_search(map);

  if (!found)
  {
    printf("\n예상대로 경로를 찾을 수 없습니다.\n");
  }

  free_map(map);
}

/**
 * 테스트 케이스 3: 미로 맵
 */
void test_maze_map()
{
  printf("\n╔════════════════════════════════════════╗\n");
  printf("║  [테스트 3] 미로 맵 (15x15)            ║\n");
  printf("╚════════════════════════════════════════╝\n\n");

  Map *map = create_map(15, 15);

  // 시작점과 목표점 설정
  set_start(map, 1, 1);
  set_end(map, 13, 13);

  // 복잡한 미로 생성
  // 세로 벽들
  for (int i = 2; i < 10; i++)
  {
    set_cell(map, 3, i, CELL_WALL);
  }
  for (int i = 5; i < 13; i++)
  {
    set_cell(map, 6, i, CELL_WALL);
  }
  for (int i = 2; i < 8; i++)
  {
    set_cell(map, 9, i, CELL_WALL);
  }
  for (int i = 10; i < 14; i++)
  {
    set_cell(map, 12, i, CELL_WALL);
  }

  // 가로 벽들
  for (int i = 7; i < 12; i++)
  {
    set_cell(map, i, 4, CELL_WALL);
  }
  for (int i = 1; i < 5; i++)
  {
    set_cell(map, i, 8, CELL_WALL);
  }
  for (int i = 9; i < 14; i++)
  {
    set_cell(map, i, 10, CELL_WALL);
  }

  printf("원본 맵:\n");
  print_map(map);

  printf("\nA* 알고리즘 실행 중...\n");
  bool found = astar_search(map);

  if (found)
  {
    printf("\n찾은 경로:\n");
    print_map(map);
  }

  free_map(map);
}

int main()
{
  printf("╔════════════════════════════════════════════════════╗\n");
  printf("║          A* 경로 찾기 알고리즘 테스트              ║\n");
  printf("║                                                    ║\n");
  printf("║  A* Algorithm: f(n) = g(n) + h(n)                 ║\n");
  printf("║  - g(n): 시작점부터의 실제 비용                   ║\n");
  printf("║  - h(n): 목표까지의 휴리스틱 (맨해튼 거리)        ║\n");
  printf("╚════════════════════════════════════════════════════╝\n");

  test_basic_map();
  test_unreachable_map();
  test_maze_map();

  printf("\n╔════════════════════════════════════════╗\n");
  printf("║  ✓ 모든 테스트가 완료되었습니다.      ║\n");
  printf("╚════════════════════════════════════════╝\n\n");

  return 0;
}