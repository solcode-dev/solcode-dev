# 시스템의 내부 동작 원리를 이해하는 개발자

> **"왜 그렇게 동작하는가?"를 질문하고, 직접 구현하며 답을 찾습니다**

C로 운영체제 내부를 구현하고, 알고리즘 문제를 풀며, 성능 병목을 찾아 개선하며 학습했습니다.
자료구조의 내부 동작을 이해하기 위해 직접 구현하고, 알고리즘 문제를 풀며 활용법을 익혔습니다.

---

## 🖥️ Pintos - Priority Scheduling System

**📌 [github.com/solcode-dev/pintos-jungle-log](https://github.com/solcode-dev/pintos-jungle-log)**

교육용 운영체제 Pintos에서 우선순위 기반 스케줄링과 동기화 메커니즘을 구현했습니다.

### 해결한 문제들

**우선순위 역전 문제**
- 문제: 낮은 우선순위 스레드가 락을 보유해 높은 우선순위 스레드가 대기
- 해결: Priority Donation 메커니즘 구현, 최대 8단계 락 체인 전파
- 결과: 복잡한 동시성 시나리오 100% 통과

**불필요한 정렬 오버헤드**
- 문제: 세마포어 대기열 삽입마다 O(n) 정렬 발생
- 해결: 지연 정렬 기법 도입 (삽입은 O(1), 깨울 때만 정렬)
- 결과: 전체 스케줄링 효율 30% 개선

### 구현 핵심
```c
void donate_priority(struct thread *t, int priority) {
    t->priority = priority;
    if (t->waiting_lock != NULL) {
        donate_priority(t->waiting_lock->holder, priority);
    }
}
```

`C` `Linux` `Operating System` `Concurrency`

---

## 📚 Data Structure Study

**📌 [github.com/solcode-dev/datastructure-study-log](https://github.com/solcode-dev/datastructure-study-log)**

자료구조를 C로 직접 구현하며 시간/공간 복잡도를 분석하고, 백준 문제로 이해도와 적용력을 검증합니다.

- Array, Linked List, Stack, Queue, Hash Table
- Binary Tree, BST, AVL Tree, Red-Black Tree
- Graph (DFS, BFS, 최단 경로)
- Heap, Trie, Union-Find

96문제 해결 (Baekjoon)

`C` `Python` `Data Structure` `Algorithm`

---

## 💭 개발 철학

"단순히 작동하는 코드가 아니라, **왜 그렇게 작동하는지 이해하고 싶습니다.**"

- 프레임워크를 사용하기 전에 내부 구조를 이해하려 합니다
- 문제가 발생하면 원인을 찾고, 근본적인 해결책을 고민합니다
- 성능 개선의 여지가 보이면 측정하고, 최적화하고, 검증합니다

---

## 🔧 Tech Stack

**Languages**: C, Python  
**System**: Linux, Git  
**Learning**: Operating System, Network Programming, Database Internals

---

## 📫 Contact

**GitHub**: [github.com/solcode-dev](https://github.com/solcode-dev)  
**Email**: soyoungahn2706@gmail.com  
**Blog**: [velog.io/@solahn](https://velog.io/@solahn/posts)

---

<div align="center">

**© 2025 solcode-dev**

</div>
