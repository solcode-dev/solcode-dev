# 컴파일러 및 플래그 설정
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
SANITIZE_FLAGS = -fsanitize=address -g
TARGET = sequential_search
OBJS = test_sequential_search.o sequential_search.o

# 기본 타겟
all: $(TARGET)

# 실행 파일 생성
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "빌드 완료: ./$(TARGET)"

# 오브젝트 파일 생성
test_sequential_search.o: test_sequential_search.c sequential_search.h
	$(CC) $(CFLAGS) -c test_sequential_search.c

sequential_search.o: sequential_search.c sequential_search.h
	$(CC) $(CFLAGS) -c sequential_search.c

# 정리
clean:
	rm -rf $(OBJS) $(TARGET)
	@echo "정리 완료"

# 실행
run: $(TARGET)
	./$(TARGET)

# 메모리 누수 검사 (Address Sanitizer 사용)
sanitize:
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) -o test_sequential_search.c
	test_sequential_search.c
	@echo "Sanitizer 빌드 완료"
	./$(TARGET)

.PHONY: all clean run sanitize