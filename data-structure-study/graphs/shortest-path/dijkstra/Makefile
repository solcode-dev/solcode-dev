# 컴파일러 및 플래그 설정
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
SANITIZE_FLAGS = -fsanitize=address -g
TARGET = dijkstra
OBJS = main.o dijkstra.o

# 기본 타겟
all: $(TARGET)

# 실행 파일 생성
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "빌드 완료: ./$(TARGET)"

# 오브젝트 파일 생성
main.o: main.c dijkstra.h
	$(CC) $(CFLAGS) -c main.c

dijkstra.o: dijkstra.c dijkstra.h
	$(CC) $(CFLAGS) -c dijkstra.c

# 정리
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "정리 완료"

# 실행
run: $(TARGET)
	./$(TARGET)

# 메모리 누수 검사 (Address Sanitizer 사용)
sanitize:
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) -o $(TARGET) main.c dijkstra.c
	@echo "Sanitizer 빌드 완료"
	./$(TARGET)

.PHONY: all clean run sanitize help