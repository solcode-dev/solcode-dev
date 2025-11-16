#include "sequential_search.h"

/**
 * 테스트 결과 출력 헬퍼 함수
 */
void print_result(int *arr, int size, int target, int result)
{
  printf("배열: ");
  print_array(arr, size);
  printf("\n찾을 값: %d\n", target);

  if (result != -1)
  {
    printf("결과: 인덱스 %d에서 발견\n", result);
  }
  else
  {
    printf("결과: 찾을 수 없음\n");
  }
  printf("\n");
}

/**
 * 테스트 1: 값이 배열의 처음에 있는 경우
 */
void test_first_position()
{
  printf("╔════════════════════════════════════════╗\n");
  printf("║  [테스트 1] 처음 위치                      ║\n");
  printf("╚════════════════════════════════════════╝\n");

  int arr[] = {10, 20, 30, 40, 50};
  int size = 5;
  int target = 10;

  int result = sequential_search(arr, size, target);
  print_result(arr, size, target, result);
}

/**
 * 테스트 2: 값이 배열의 중간에 있는 경우
 */
void test_middle_position()
{
  printf("╔════════════════════════════════════════╗\n");
  printf("║  [테스트 2] 중간 위치                      ║\n");
  printf("╚════════════════════════════════════════╝\n");

  int arr[] = {5, 2, 8, 1, 9};
  int size = 5;
  int target = 8;

  int result = sequential_search(arr, size, target);
  print_result(arr, size, target, result);
}

/**
 * 테스트 3: 값이 배열의 끝에 있는 경우
 */
void test_last_position()
{
  printf("╔════════════════════════════════════════╗\n");
  printf("║  [테스트 3] 마지막 위치                     ║\n");
  printf("╚════════════════════════════════════════╝\n");

  int arr[] = {3, 7, 1, 9, 15};
  int size = 5;
  int target = 15;

  int result = sequential_search(arr, size, target);
  print_result(arr, size, target, result);
}

/**
 * 테스트 4: 값이 배열에 없는 경우
 */
void test_not_found()
{
  printf("╔═══════════════════════════════════════╗\n");
  printf("║  [테스트 4] 값이 없는 경우                 ║\n");
  printf("╚═══════════════════════════════════════╝\n");

  int arr[] = {2, 4, 5, 6, 10};
  int size = 5;
  int target = 89;

  int result = sequential_search(arr, size, target);
  print_result(arr, size, target, result);
}

/**
 * 테스트 5: 빈 배열인 경우
 */
void test_empty_array()
{
  printf("╔════════════════════════════════════════╗\n");
  printf("║  [테스트 5] 빈 배열                        ║\n");
  printf("╚════════════════════════════════════════╝\n");

  int *arr = NULL;
  int size = 0;
  int target = 5;

  int result = sequential_search(arr, size, target);
  print_result(arr, size, target, result);
}

/**
 * 테스트 6: 중복 값이 있는 경우
 */
void test_duplicate_values()
{
  printf("╔════════════════════════════════════════╗\n");
  printf("║  [테스트 6] 중복 값 (첫 번째 반환)           ║\n");
  printf("╚════════════════════════════════════════╝\n");

  int arr[] = {3, 6, 4, 5, 6};
  int size = 5;
  int target = 6;

  printf("===> 값 6이 인덱스 1, 4에 있음\n\n");

  int result = sequential_search(arr, size, target);
  print_result(arr, size, target, result);
}

/**
 * 테스트 7: 큰 배열 (동적 할당)
 */
void test_large_array()
{
  printf("╔════════════════════════════════════════╗\n");
  printf("║  [테스트 7] 동적 할당 배열                  ║\n");
  printf("╚════════════════════════════════════════╝\n");

  int size = 10;
  int *arr = (int *)malloc(size * sizeof(int));

  // 배열 초기화: 0, 10, 20, 30, ... , 90
  for (int i = 0; i < size; i++)
  {
    arr[i] = i * 10;
  }

  int target = 50;
  int result = sequential_search(arr, size, target);
  print_result(arr, size, target, result);

  // 메모리 해제
  free(arr);
  printf("동적 메모리 해제 완료\n\n");
}

int main()
{
  printf("╔══════════════════════════════════════════════╗\n");
  printf("║      순차 탐색 알고리즘 (Sequential Search)       ║\n");
  printf("║                                              ║\n");
  printf("║  시간 복잡도: O(n)                              ║\n");
  printf("║  공간 복잡도: O(1)                              ║\n");
  printf("╚══════════════════════════════════════════════╝\n\n");

  test_first_position();
  test_middle_position();
  test_last_position();
  test_not_found();
  test_empty_array();
  test_duplicate_values();
  test_large_array();

  printf("✓ 모든 테스트가 완료되었습니다.\n");

  return 0;
}