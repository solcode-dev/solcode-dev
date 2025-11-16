## 시스템의 내부 동작 원리를 이해하는 개발자

> **"왜 그렇게 동작하는가?"를 질문하고, 직접 구현하며 답을 찾습니다**

C로 운영체제 내부를 구현하고, 알고리즘 문제를 풀며, 성능 병목을 찾아 개선하며 학습했습니다.
자료구조의 내부 동작을 이해하기 위해 직접 구현하고, 알고리즘 문제를 풀며 활용법을 익혔습니다.

---
이 저장소는 포트폴리오용 통합 저장소입니다.<Br/> 운영체제 구현과 자료구조 학습 내역을 한 곳에서 확인할 수 있도록 구성했습니다.

## 📂 저장소 구조

이 저장소는 두 개의 독립 프로젝트를 Git Subtree로 통합했습니다:
```bash
solcode-dev/ 
├── pintos/ # 운영체제 구현 프로젝트 
    └── 원본: github.com/solcode-dev/pintos-jungle-log 
└── data-structure-study/ # 자료구조 학습 프로젝트 
    └── 원본: github.com/solcode-dev/datastructure-study-log
```
💡 각 프로젝트는 독립적으로 개발/관리되며, 이 저장소에서 통합 버전을 확인할 수 있습니다.

---

## 🖥️ Pintos - Priority Scheduling System

**📁 [/pintos](/pintos)** | **📌 원본 저장소: [pintos-jungle-log](https://github.com/solcode-dev/pintos-jungle-log)**

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

`C` `Linux` `Operating System` `Concurrency` `Priority Scheduling`

---

## 📚 Data Structure Study

**📁 [/data-structure-study](/data-structure-study/) | 📌 원본 저장소: [datastructure-study-log](https://github.com/solcode-dev/datastructure-study-log)**

자료구조를 C로 직접 구현하며 시간/공간 복잡도를 분석했습니다.
학습 후에는 백준 문제로 이해도와 적용력을 확인했습니다.

### 구현한 자료 구조
- 탐색: 이진 탐색, 순차 탐색
- 그래프 탐색: BFS, DFS
- 최단 경로: 다익스트라, A* 알고리즘
- 최소 신장 트리: Kruskal, Prim, 개선된 Prim

### 학습 성과
✅ 백준 96문제 해결 (Python 사용)
🔍 실제 문제 적용을 통한 활용 능력 검증

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
**Learning**: Operating System, Network Programming

---

## 📫 Contact

**GitHub**: [github.com/solcode-dev](https://github.com/solcode-dev)  
**Email**: soyoungahn2706@gmail.com  
**Blog**: [velog.io/@solahn](https://velog.io/@solahn/posts)

---

<div align="center">

**© 2025 solcode-dev**

</div>
