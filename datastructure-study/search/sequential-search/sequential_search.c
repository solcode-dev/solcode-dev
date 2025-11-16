#include "sequential_search.h"

/**
 * 순차 탐색 알고리즘 구현
 *
 * 시간 복잡도:
 * - 최선: O(1) - 첫번째 원소가 타겟
 * - 평균: O(n)
 * - 최악: O(n) - 마지막 원소이거나 없는 경우
 *
 * 공간 복잡도: O(1)
 *
 * @param arr: 검색할 정수 배열
 * @param size: 배열의 크기
 * @param target: 찾을 값
 * @return: 찾은 경우 인덱스, 없으면 -1
 */
int sequential_search(int *arr, int size, int target)
{
  // 빈 배열 처리
  if (arr == NULL || size <= 0)
  {
    return -1;
  }

  // 배열을 처음부터 끝까지 순차적으로 탐색
  for (int i = 0; i < size; i++)
  {
    if (arr[i] == target)
    {
      return i; // 찾으면 인덱스 반환
    }
  }

  // 못 찾으면 -1 반환
  return -1;
}

/**
 * 배열 출력
 */
void print_array(int *arr, int size)
{
  if (arr == NULL || size <= 0)
  {
    printf("[]");
    return;
  }

  printf("[");
  for (int i = 0; i < size; i++)
  {
    printf("%d", arr[i]);
    if (i < size - 1)
    {
      printf(", ");
    }
  }
  printf("]");
}