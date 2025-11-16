#include "linked_list.h"

int main(void)
{
  int i = 0;
  int count = 0;
  Node *list = NULL;
  Node *current = NULL;
  Node *new_node = NULL;

  // 노드 5개 추가
  for (i = 0; i < 5; i++)
  {
    new_node = create_node(i);
    append_node(&list, new_node);
  }

  new_node = create_node(-1);
  insert_new_head(&list, new_node);

  new_node = create_node(-2);
  insert_new_head(&list, new_node);

  // 리스트 출력
  count = get_node_count(list);
  for (i = 0; i < count; i++)
  {
    current = get_node_at(list, i);
    printf("list[%d]: %d\n", i, current->data);
  }

  // 리스트의 세번째 노드 뒤에 새 노드 삽입
  printf("\nInserting 3000 after [2]...\n\n");

  current = get_node_at(list, 2);
  new_node = create_node(3000);

  insert_after(current, new_node);

  // 리스트 출력
  count = get_node_count(list);
  for (i = 0; i < count; i++)
  {
    current = get_node_at(list, i);
    printf("list[%d]: %d\n", i, current->data);
  }

  // insert_before 테스트: 네번째 노드(3000) 앞에 새 노드 삽입
  printf("\nInserting 2500 before [3] (value: 3000)...\n\n");

  current = get_node_at(list, 3);
  new_node = create_node(2500);

  insert_before(&list, current, new_node);

  // 리스트 출력
  count = get_node_count(list);
  for (i = 0; i < count; i++)
  {
    current = get_node_at(list, i);
    printf("list[%d]: %d\n", i, current->data);
  }

  // insert_before 테스트: head 앞에 새 노드 삽입
  printf("\nInserting -100 before head...\n\n");

  current = get_node_at(list, 0);
  new_node = create_node(-100);

  insert_before(&list, current, new_node);

  // 리스트 출력
  count = get_node_count(list);
  for (i = 0; i < count; i++)
  {
    current = get_node_at(list, i);
    printf("list[%d]: %d\n", i, current->data);
  }

  // ========================================
  // destroy_node 테스트: 개별 노드 제거
  // ========================================
  printf("\n=== destroy_node 테스트 ===\n");
  printf("Removing Node at [2] (value should be 0)...\n\n");

  current = get_node_at(list, 2);
  printf("Removing Node with value: %d\n", current->data);
  remove_node(&list, current);
  destroy_node(current);

  // 리스트 출력
  count = get_node_count(list);
  printf("After removal, list has %d nodes:\n", count);
  for (i = 0; i < count; i++)
  {
    current = get_node_at(list, i);
    printf("list[%d]: %d\n", i, current->data);
  }

  // ========================================
  // destroy_all_nodes 테스트: 전체 리스트 삭제
  // ========================================
  printf("\n=== destroy_all_nodes 테스트 ===\n");
  printf("Before destroy_all_nodes:\n");
  printf("  list pointer: %p\n", (void *)list);
  printf("  Node count: %d\n", count);

  destroy_all_nodes(&list);

  printf("\nAfter destroy_all_nodes:\n");
  printf("  list pointer: %p (should be NULL)\n", (void *)list);
  printf("  Node count: %d\n", get_node_count(list));

  // 안전성 테스트: NULL 리스트에 노드 추가
  printf("\n=== NULL 리스트에 노드 추가 테스트 ===\n");
  if (list == NULL)
  {
    printf("List is safely NULL. Adding new nodes...\n");
    new_node = create_node(100);
    append_node(&list, new_node);
    new_node = create_node(200);
    append_node(&list, new_node);

    count = get_node_count(list);
    printf("New list has %d nodes:\n", count);
    for (i = 0; i < count; i++)
    {
      current = get_node_at(list, i);
      printf("list[%d]: %d\n", i, current->data);
    }

    // 최종 정리
    destroy_all_nodes(&list);
    printf("\nFinal cleanup done. list pointer: %p\n", (void *)list);
  }

  return 0;
}
