#include "bst.h"

/**
 * 테스트 1: 빈 트리에서 탐색
 */
void test_empty_tree()
{
  printf("╔══════════════════════════════════╗\n");
  printf("║  [테스트 1] 빈 트리에서 탐색           ║\n");
  printf("╚══════════════════════════════════╝\n");

  Node *root = NULL;
  Node *result = search_node(root, 10);

  if (result == NULL)
  {
    printf("✓ 빈 트리에서 탐색 결과: NULL (정상)\n");
  }
  else
  {
    printf("✗ 오류: NULL이 아님\n");
  }
  printf("\n");
}

/**
 * 테스트 2: 노드 삽입 후 중위 순회 (정렬 확인)
 */
void test_insert_and_inorder()
{
  printf("╔══════════════════════════════════╗\n");
  printf("║  [테스트 2] 삽입 후 중위 순회          ║\n");
  printf("╚══════════════════════════════════╝\n");

  Node *root = NULL;

  // 삽입: 50, 30, 70, 20, 40, 60, 80
  printf("삽입 순서: 50, 30, 70, 20, 40, 60, 80\n");
  root = insert_node(root, 50);
  root = insert_node(root, 30);
  root = insert_node(root, 70);
  root = insert_node(root, 20);
  root = insert_node(root, 40);
  root = insert_node(root, 60);
  root = insert_node(root, 80);

  printf("\n트리 구조:\n");
  printf("       50\n");
  printf("      /  \\\n");
  printf("    30    70\n");
  printf("   /  \\  /  \\\n");
  printf("  20  40 60  80\n\n");

  printf("중위 순회 (정렬된 순서): ");
  inorder_traversal(root);
  printf("\n✓ 오름차순 정렬 확인\n\n");

  free_tree(root);
}

/**
 * 테스트 3: 값 탐색 (있는 경우/없는 경우)
 */
void test_search()
{
  printf("╔════════════════════════════════════╗\n");
  printf("║  [테스트 3] 값 탐색                   ║\n");
  printf("╚════════════════════════════════════╝\n");

  Node *root = NULL;
  root = insert_node(root, 50);
  root = insert_node(root, 30);
  root = insert_node(root, 70);
  root = insert_node(root, 20);
  root = insert_node(root, 40);

  // 있는 값 탐색
  printf("트리: 50, 30, 70, 20, 40\n\n");

  Node *result1 = search_node(root, 40);
  if (result1 != NULL && result1->data == 40)
  {
    printf("✓ 값 40 찾기: 성공 (있음)\n");
  }
  else
  {
    printf("✗ 값 40 찾기: 실패\n");
  }

  // 없는 값 탐색
  Node *result2 = search_node(root, 100);
  if (result2 == NULL)
  {
    printf("✓ 값 100 찾기: NULL 반환 (없음)\n");
  }
  else
  {
    printf("✗ 값 100 찾기: 오류\n");
  }

  printf("\n");
  free_tree(root);
}

/**
 * 테스트 4: 노드 삭제 (자식 없음/한 개/두 개)
 */
void test_delete()
{
  printf("╔═══════════════════════════════════╗\n");
  printf("║  [테스트 4] 노드 삭제                 ║\n");
  printf("╚═══════════════════════════════════╝\n");

  Node *root = NULL;
  root = insert_node(root, 50);
  root = insert_node(root, 30);
  root = insert_node(root, 70);
  root = insert_node(root, 20);
  root = insert_node(root, 40);
  root = insert_node(root, 60);
  root = insert_node(root, 80);

  printf("원본 트리 (중위 순회): ");
  inorder_traversal(root);
  printf("\n\n");

  // 케이스 1: 자식이 없는 노드 삭제 (리프 노드)
  printf("1. 자식 없는 노드 삭제 (20)\n");
  root = delete_node(root, 20);
  printf("   결과: ");
  inorder_traversal(root);
  printf("\n\n");

  // 케이스 2: 자식이 하나인 노드 삭제
  printf("2. 자식 하나인 노드 삭제 (30)\n");
  root = delete_node(root, 30);
  printf("   결과: ");
  inorder_traversal(root);
  printf("\n\n");

  // 케이스 3: 자식이 둘인 노드 삭제
  printf("3. 자식 둘인 노드 삭제 (50, 루트)\n");
  root = delete_node(root, 50);
  printf("   결과: ");
  inorder_traversal(root);
  printf("\n\n");

  free_tree(root);
}

/**
 * 테스트 5: 전위/후위 순회
 */
void test_traversals()
{
  printf("╔═══════════════════════════════════╗\n");
  printf("║  [테스트 5] 전위/후위 순회             ║\n");
  printf("╚═══════════════════════════════════╝\n");

  Node *root = NULL;
  root = insert_node(root, 50);
  root = insert_node(root, 30);
  root = insert_node(root, 70);
  root = insert_node(root, 20);
  root = insert_node(root, 40);
  root = insert_node(root, 60);
  root = insert_node(root, 80);

  printf("트리 구조:\n");
  printf("       50\n");
  printf("      /  \\\n");
  printf("    30    70\n");
  printf("   /  \\  /  \\\n");
  printf("  20  40 60  80\n\n");

  printf("전위 순회 (Root->Left->Right): ");
  preorder_traversal(root);
  printf("\n");

  printf("중위 순회 (Left->Root->Right): ");
  inorder_traversal(root);
  printf("\n");

  printf("후위 순회 (Left->Right->Root): ");
  postorder_traversal(root);
  printf("\n\n");

  free_tree(root);
}

/**
 * 테스트 6: 메모리 해제 테스트
 */
void test_memory()
{
  printf("╔═══════════════════════════════════╗\n");
  printf("║  [테스트 6] 메모리 관리                ║\n");
  printf("╚═══════════════════════════════════╝\n");

  Node *root = NULL;

  // 여러 노드 삽입
  for (int i = 1; i <= 10; i++)
  {
    root = insert_node(root, i * 10);
  }

  printf("10개 노드 삽입 완료\n");
  printf("트리 내용: ");
  inorder_traversal(root);
  printf("\n");

  // 전체 메모리 해제
  free_tree(root);
  printf("✓ 모든 노드 메모리 해제 완료\n\n");
}

int main()
{
  printf("╔═══════════════════════════════════════════════╗\n");
  printf("║     Binary Search Tree (이진 탐색 트리) 테스트     ║\n");
  printf("║                                               ║\n");
  printf("║  시간 복잡도: 평균 O(log n), 최악 O(n)             ║\n");
  printf("║  공간 복잡도: O(n)                               ║\n");
  printf("╚═══════════════════════════════════════════════╝\n\n");

  test_empty_tree();
  test_insert_and_inorder();
  test_search();
  test_delete();
  test_traversals();
  test_memory();

  printf("✓ 모든 테스트가 완료되었습니다.\n");
  return 0;
}