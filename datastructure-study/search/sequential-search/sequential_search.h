#ifndef SEQUENTIAL_SEARCH_H
#define SEQUENTIAL_SEARCH_H

#include <stdio.h>
#include <stdlib.h>

/**
 * 순차 탐색 함수
 * @param arr: 검색할 정수 배열
 * @param size: 배열의 크기
 * @param target: 찾을 값
 * @return: 찾은 경우 인덱스, 없으면 -1
 */
int sequential_search(int *arr, int size, int target);

/**
 * 배열 출력 함수
 * @param arr: 출력할 배열
 * @param size: 배열의 크기
 */
void print_array(int *arr, int size);

#endif // SEQUENTIAL_SEARCH_H