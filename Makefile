CC=gcc
CFLAGS=-Wall -Wextra -std=c99
OBJS=BlockSpwan.o PanData.o BlockData.o
TEST_BIN=tests

all: $(TEST_BIN)

$(TEST_BIN): test.o $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

test.o: test.c BlockSpwan.h PanData.h
	$(CC) $(CFLAGS) -c $< -o $@

BlockSpwan.o: BlockSpwan.c BlockSpwan.h BlockData.h
	$(CC) $(CFLAGS) -c $< -o $@

PanData.o: PanData.c PanData.h
	$(CC) $(CFLAGS) -c $< -o $@

BlockData.o: BlockData.c BlockData.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: test clean

test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -f $(TEST_BIN) *.o
