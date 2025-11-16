#include "bst.h"

/**
 * 새로운 노드 생성
 * @param data: 노드에 저장할 값
 * @return: 생성된 노드 포인터
 */
Node *create_node(int data)
{
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}

/**
 * BST에 값 삽입
 * @param root: 트리의 루트 노드
 * @param data: 삽입할 값
 * @return: 삽입 후 루트 노드
 *
 * 시간 복잡도: 평균 O(log n), 최악 O(n)
 */
Node *insert_node(Node *root, int data)
{
  // 빈 트리이거나 삽입 위치에 도달
  if (root == NULL)
  {
    return create_node(data);
  }

  // 작으면 왼쪽 서브트리로
  if (data < root->data)
  {
    root->left = insert_node(root->left, data);
  }
  // 크면 오른쪽 서브트리로
  else if (data > root->data)
  {
    root->right = insert_node(root->right, data);
  }
  // 같은 값은 무시 (중복 허용 안 함)

  return root;
}

/**
 * BST에서 값 탐색
 * @param root: 트리의 루트 노드
 * @param data: 찾을 값
 * @return: 찾은 노드, 없으면 NULL
 *
 * 시간 복잡도: 평균 O(log n), 최악 O(n)
 */
Node *search_node(Node *root, int data)
{
  // 빈 트리이거나 찾았음
  if (root == NULL || root->data == data)
  {
    return root;
  }

  // 작으면 왼쪽 서브트리에서 탐색
  if (data < root->data)
  {
    return search_node(root->left, data);
  }

  // 크면 오른쪽 서브트리에서 탐색
  return search_node(root->right, data);
}

/**
 * 서브트리에서 최솟값 노드 찾기 (가장 왼쪽 노드)
 * @param root: 서브트리의 루트
 * @return: 최솟값을 가진 노드
 */
Node *find_min(Node *root)
{
  while (root != NULL && root->left != NULL)
  {
    root = root->left;
  }
  return root;
}

/**
 * BST에서 값 삭제
 * @param root: 트리의 루트 노드
 * @param data: 삭제할 값
 * @return: 삭제 후 루트 노드
 *
 * 3가지 케이스:
 * 1. 자식이 없는 경우 (리프 노드) - 그냥 삭제
 * 2. 자식이 하나인 경우 - 자식으로 대체
 * 3. 자식이 둘인 경우 - 오른쪽 서브트리의 최솟값으로 대체
 */
Node *delete_node(Node *root, int data)
{
  if (root == NULL)
  {
    return NULL;
  }

  // 삭제할 노드 찾기
  if (data < root->data)
  {
    root->left = delete_node(root->left, data);
  }
  else if (data > root->data)
  {
    root->right = delete_node(root->right, data);
  }
  else
  {
    // 찾았음! 삭제 처리

    // 케이스 1: 자식이 없거나 하나만 있는 경우
    if (root->left == NULL)
    {
      Node *temp = root->right;
      free(root);
      return temp;
    }
    else if (root->right == NULL)
    {
      Node *temp = root->left;
      free(root);
      return temp;
    }

    // 케이스 3: 자식이 둘 다 있는 경우
    // 오른쪽 서브트리의 최솟값 찾기
    Node *temp = find_min(root->right);

    // 최솟값을 현재 노드로 복사
    root->data = temp->data;

    // 오른쪽 서브트리에서 최솟값 삭제
    root->right = delete_node(root->right, temp->data);
  }

  return root;
}

/**
 * 중위 순회 (Inorder: Left -> Root -> Right)
 * BST에서는 오름차순 정렬된 순서로 출력됨
 */
void inorder_traversal(Node *root)
{
  if (root != NULL)
  {
    inorder_traversal(root->left);
    printf("%d ", root->data);
    inorder_traversal(root->right);
  }
}

/**
 * 전위 순회 (Preorder: Root -> Left -> Right)
 */
void preorder_traversal(Node *root)
{
  if (root != NULL)
  {
    printf("%d ", root->data);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
  }
}

/**
 * 후위 순회 (Postorder: Left -> Right -> Root)
 */
void postorder_traversal(Node *root)
{
  if (root != NULL)
  {
    postorder_traversal(root->left);
    postorder_traversal(root->right);
    printf("%d ", root->data);
  }
}

/**
 * 트리 전체 메모리 해제 (후위 순회 방식)
 * @param root: 트리의 루트 노드
 */
void free_tree(Node *root)
{
  if (root != NULL)
  {
    free_tree(root->left);
    free_tree(root->right);
    free(root);
  }
}