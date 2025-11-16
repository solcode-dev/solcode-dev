CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SANITIZE = -fsanitize=address -fno-omit-frame-pointer
TARGET = bfs_demo
TEST_TARGET = test_bfs

# 소스 파일
SOURCES = bfs.c main.c
TEST_SOURCES = bfs.c test_bfs.c

# 오브젝트 파일
OBJECTS = $(SOURCES:.c=.o)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

# 기본 타겟
all: $(TARGET)

# 메인 프로그램 컴파일
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# 테스트 프로그램 컴파일
$(TEST_TARGET): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# 오브젝트 파일 생성 규칙
%.o: %.c bfs.h
	$(CC) $(CFLAGS) -c $< -o $@

# 테스트 실행
test: $(TEST_TARGET)
	@echo "=== 유닛 테스트 실행 ==="
	./$(TEST_TARGET)

# 메모리 누수 검사 (sanitizer 사용)
memcheck: CFLAGS += $(SANITIZE)
memcheck: clean $(TARGET) $(TEST_TARGET)
	@echo "=== 메모리 검사 (메인 프로그램) ==="
	./$(TARGET)
	@echo ""
	@echo "=== 메모리 검사 (테스트) ==="
	./$(TEST_TARGET)

# 실행
run: $(TARGET)
	./$(TARGET)

# 정리
clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o

# Phony 타겟
.PHONY: all test memcheck run clean