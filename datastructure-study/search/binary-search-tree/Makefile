# 컴파일러 및 플래그 설정
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
SANITIZE_FLAGS = -fsanitize=address -g
TARGET = test_bst
OBJS = test_bst.o bst.o

# 기본 타겟
all: $(TARGET)

# 실행 파일 생성
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "빌드 완료: ./$(TARGET)"

# 오브젝트 파일 생성
test_bst.o: test_bst.c bst.h
	$(CC) $(CFLAGS) -c test_bst.c

bst.o: bst.c bst.h
	$(CC) $(CFLAGS) -c bst.c

# 정리
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "정리 완료"

# 실행
run: $(TARGET)
	./$(TARGET)

# Address Sanitizer (메모리 누수 검사)
sanitize:
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) -g -o $(TARGET)_debug test_bst.c bst.c
	./$(TARGET)_debug
	@echo "Sanitizer 빌드 완료"
	./$(TARGET)

.PHONY: all clean run sanitize