# Pintos: 우선순위 스케줄링 구현

Pintos 교육용 운영체제에서 우선순위 기반 스레드 스케줄링을 시스템 수준으로 구현한 프로젝트입니다.

## 개요

이 프로젝트에서는 우선순위 역전(priority inversion)을 방지하기 위한 우선순위 기부(priority donation) 메커니즘과 세마포어/락 관리를 통해, 
교착 상태(deadlock)나 기아(starvation) 없이 복잡한 동시성 작업을 구현했습니다

## 아키텍처

### 스레드 구조
```c
struct thread {
    int priority;                    // 현재 우선순위
    int original_priority;           // 기부받기 전의 우선순위
    struct list donators;            // 이 스레드에게 기부한 스레드들
    struct lock *waiting_lock;       // 이 스레드가 대기 중인 락
    struct list_elem donation_elem;  // donators 리스트용 요소
    // ... 다른 필드들
};
```

### 락과 세마포어 설계
```
락 (이진 자원)
├── holder: 현재 소유 스레드
└── semaphore: 접근 제어 (값: 0 또는 1)
    ├── value: 사용 가능한 개수
    └── waiters: 대기 스레드 리스트 (sema_up() 시점에 정렬)

조건 변수
└── waiters: semaphore_elem 구조체 리스트 (cond_signal() 시점에 정렬)
    └── 각 요소는 스레드 조정용 개별 세마포어 포함

ready_list (전역 변수)
└── thread.h에 extern 선언되어 다른 모듈에서 접근 가능
```
## 핵심 함수

| 함수 | 목적 |
|------|------|
| `sema_down()` | waiters에 `list_push_back()`으로 스레드 추가 후 블록 |
| `sema_up()` | waiters를 정렬 후 최고 우선순위 스레드를 깨움 |
| `lock_acquire()` | 우선순위 기부를 지원하는 락 획득 |
| `lock_release()` | 락 해제 및 우선순위 재계산 |
| `donate_priority()` | 락 체인을 통한 우선순위 전파 |
| `recalculate_priority()` | donators 리스트 기반 우선순위 재계산 |
| `remove_donations()` | 특정 락과 관련된 기부만 선택적으로 제거 |
| `cond_wait()` | waiters에 `list_push_back()`으로 추가 후 대기 |
| `cond_signal()` | waiters 정렬 후 최고 우선순위 스레드 깨우기 |
| `preemption_by_priority()` | 선점 필요 여부 확인 및 수행 |
| `compare_ready_priority()` | 스레드 우선순위 비교 함수 (내림차순) |
| `compare_donation_priority()` | donators 리스트 정렬용 비교 함수 |

## 사용 예제

```c
// 동기화 원시 요소 초기화
struct lock resource_lock;
struct condition data_ready;
lock_init(&resource_lock);
cond_init(&data_ready);

// 자동 우선순위 기부를 지원하는 임계 섹션
lock_acquire(&resource_lock);
// ... 보호된 코드 ...
if (condition_met) {
    cond_signal(&data_ready, &resource_lock);
}
lock_release(&resource_lock);

// 조건 변수를 이용한 대기
lock_acquire(&resource_lock);
while (!condition_met) {
    cond_wait(&data_ready, &resource_lock);
}
// ... 보호된 데이터로 진행 ...
lock_release(&resource_lock);
```

## 테스트

다음을 포함하는 우선순위 스케줄링 테스트 케이스를 통과합니다:
- 준비 큐에서의 우선순위 순서 지정
- 우선순위 역전 방지 우선순위 기부
- 깊은 기부 전파를 지원하는 중첩 락 체인
- 조건 변수 우선순위 의미론
- 올바른 우선순위 복원을 지원하는 락 해제

  
## 파일 구성

### 핵심 구현 파일
- `pintos/include/threads/synch.h` - 동기화 원시 요소 헤더
- `pintos/threads/synch.c` - 세마포어, 락, 조건 변수 구현
- `pintos/include/threads/thread.h` - 스레드 구조체, ready_list extern 선언, 우선순위 함수 선언
- `pintos/threads/thread.c` - 스레드 초기화, 스케줄링, ready_list 정의

### 리스트 라이브러리
- `pintos/include/lib/kernel/list.h` - 리스트 자료구조 인터페이스
- `pintos/lib/kernel/list.c` - 리스트 구현, 성능 측정 함수 포함

### 테스트 파일
- `pintos/tests/threads/priority-donate-one.c` - 단일 락 우선순위 기부 테스트
- `pintos/tests/threads/priority-donate-multiple.c` - 다중 락 우선순위 기부 테스트
- `pintos/tests/threads/priority-donate-sema.c` - 세마포어 우선순위 기부 테스트

## 향후 개선 사항

- 락 경합(lock contention) 시나리오 추가 성능 최적화
- ready_list 재정렬 빈도 최소화 방안 검토

## 참고 자료
[Pintos 공식 문서](https://casys-kaist.github.io/pintos-kaist/)


